/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:35:11 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/07 13:41:05 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_signal	g_signal;

/**
 * @brief Handles incoming signals for minishell
 * 
 * SIGINT: CTRL+C, SIGQUIT: CTRL+\ and CTRL+D (EOF) are handled
 * acording to the current mode of the shell,
 * either interactive (READLINE_MODE) or execution (EXECUTION_MODE).
 * 
 * @param signum The signal number to be handled
 * 
 * @return void
 */
void	signal_handler(int signum)
{
	if (signum == SIGINT && g_signal == READLINE_MODE)
	{
		//rl_replace_line("", 0);
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT && g_signal == READLINE_MODE)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGINT && g_signal == EXECUTION_MODE)
	{
		g_signal = INSIGINT;
	}
	else if (signum == SIGQUIT && g_signal == EXECUTION_MODE)
	{
		g_signal = INSIGQUIT;
	}
}

int	init_data(t_data *data, char **envp)
{
	// TODO: initialize env_arr right before execve
	data->env_arr = NULL;
	data->envp = NULL;
	data->tokens = NULL;
	data->exit_status = EXIT_SUCCESS;
	data->tree = NULL;
	init_env(data, envp);
	init_builtin(data);
	return (data->exit_status);
}

/**
 * Disables the echoing of control characters (CTRL+C, CTRL+\)
 * in the terminal. This function modifies the terminal attributes to
 * prevent control characters from being displayed when entered.
 * 
 * @param disable If TRUE, disable echoing; if FALSE, restore original settings
 * @return int Returns 0 on success, -1 on failure
 */
int	disable_echoctl(int disable)
{
	struct termios			term;
	static struct termios	term_old;

	if (disable)
	{
		if (tcgetattr(STDIN_FILENO, &term) == -1)
			return (EXIT_FAILURE);
		term_old = term;
		term.c_lflag &= ~ECHOCTL;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term_old) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	main_loop(t_data *data)
{
	char	*line;

	while (TRUE)
	{
		if (g_signal == INSIGINT)
			ft_fprintf(STDERR_FILENO, "^C\n");
		else if (g_signal == INSIGQUIT)
			ft_fprintf(STDERR_FILENO, "^\\Quit (core dumped)\n");
		g_signal = READLINE_MODE;
		line = readline(SHELL_PROMPT);
		g_signal = EXECUTION_MODE;
		if (!line)
		{
			data->exit_status = EXIT_SUCCESS;
			ft_exit(data, NULL, 0);
		}
		data->tokens = lexer(data, line);
		if (data->tokens)
		{
			add_history(line);
			if (DEBUG)
				print_tokens(data->tokens);
			data->tree = build_tree(data, data->tokens, NULL);
			if (DEBUG)
				display_tree(data->tree);
			if (data->tree)
				ft_run_ast(data, data->tree);
		}
		free(line);
		free_tree(data->tree);
		data->tree = NULL;
		free_tokens(data->tokens);
		data->tokens = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data				data;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	if (init_data(&data, envp) != EXIT_SUCCESS)
		return (data.exit_status);
	disable_echoctl(TRUE);
	main_loop(&data);
	return (EXIT_SUCCESS);
}
