/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:35:11 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/17 19:50:26 by vviterbo         ###   ########.fr       */
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
}

int	init_data(t_data *data, char **envp)
{
	if (save_std_streams(data) != EXIT_SUCCESS)
		return (data->exit_status);
	data->env_arr = NULL;
	data->envp = NULL;
	data->tokens = NULL;
	data->exit_status = EXIT_SUCCESS;
	data->last_exit_status = EXIT_SUCCESS;
	data->tree = NULL;
	init_env(data, envp);
	init_builtin(data);
	return (data->exit_status);
}

void	main_loop(t_data *data)
{
	char	*line;

	while (TRUE)
	{
		g_signal = READLINE_MODE;
		line = readline(SHELL_PROMPT); 
		errno = EXIT_SUCCESS;
		//TODO: why does readline sets errno = 2 ? (on first pass ?)
		g_signal = EXECUTION_MODE;
		if (!line)
		{
			data->exit_status = EXIT_SUCCESS;
			ft_exit(data, NULL, 0);
		}
		data->last_exit_status = data->exit_status;
		data->exit_status = EXIT_SUCCESS;
		lexer(data, line);
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

	(void)argc;
	(void)argv;
	set_signal(SIGINT, signal_handler);
	set_signal(SIGQUIT, SIG_IGN);
	if (init_data(&data, envp) != EXIT_SUCCESS)
		return (data.exit_status);
	main_loop(&data);
	return (EXIT_SUCCESS);
}
