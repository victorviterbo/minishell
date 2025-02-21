/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:35:11 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/17 03:34:42 by vbronov          ###   ########.fr       */
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
		rl_replace_line("", 0);
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
	data->env_arr = NULL;
	data->envp = NULL;
	data->exit_status = EXIT_SUCCESS;
	return (init_env(data, envp));
}

/**
 * Disables the echoing of control characters (CTRL+C, CTRL+\)
 * in the terminal. This function modifies the terminal attributes to
 * prevent control characters from being displayed when entered.
 * 
 * @return int Returns 0 on success, -1 on failure
 */
int	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	main_loop(t_data *data)
{
	char	*line;

	while (TRUE)
	{
		if (g_signal == INSIGINT)
			ft_fprintf(2, "^C\n");
		else if (g_signal == INSIGQUIT)
			ft_fprintf(2, "^\\Quit (core dumped)\n");
		g_signal = READLINE_MODE;
		line = readline(SHELL_PROMPT);
		g_signal = EXECUTION_MODE;
		if (!line)
		{
			data->exit_status = EXIT_SUCCESS;
			ft_exit(data, NULL, 0);
		}
		// TODO: add here tokenization logic
		if (line[0] != '\0')
			add_history(line);
		free(line);
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
	disable_echoctl();
	main_loop(&data);
	return (EXIT_SUCCESS);
}
