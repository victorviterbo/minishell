/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:35:11 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/27 03:37:58 by vbronov          ###   ########.fr       */
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
	if (signum == SIGINT
		&& (g_signal == READLINE_MODE || g_signal == GOT_SIGINT))
	{
		g_signal = GOT_SIGINT;
		rl_replace_line("", 0);
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

static int	init_data(t_data *data, char **envp)
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

static void	process_line(t_data *data, char *line)
{
	lexer(data, line);
	if (data->tokens)
	{
		data->last_exit_status = data->exit_status;
		data->exit_status = EXIT_SUCCESS;
		add_history(line);
		if (DEBUG)
			print_tokens(data->tokens);
		if (syntax_check(data, data->tokens) != EXIT_SUCCESS)
			return ;
		data->tree = build_tree(data, data->tokens, NULL);
		prepare_heredocs(data, data->tree);
		if (DEBUG)
			display_tree(data->tree);
		if (data->exit_status == EXIT_SUCCESS)
			ft_run_ast(data, data->tree);
	}
}

static void	main_loop(t_data *data)
{
	char	*line;

	while (TRUE)
	{
		g_signal = READLINE_MODE;
		line = readline(SHELL_PROMPT);
		if (g_signal == GOT_SIGINT)
		{
			data->exit_status = 130;
			data->last_exit_status = data->exit_status;
		}
		g_signal = EXECUTION_MODE;
		if (!line)
			ft_exit(data, NULL, 0);
		process_line(data, line);
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
