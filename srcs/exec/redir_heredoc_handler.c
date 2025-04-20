/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 03:30:24 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/20 03:35:02 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_quoted_delimiter(t_data *data, char **delimiter)
{
	int		*isescaped;

	isescaped = parse_quote_positions(data, *delimiter);
	if (isescaped)
	{
		remove_quotes(*delimiter, isescaped);
		free(isescaped);
	}
}

static int	handle_heredoc(t_data *data, char *delimiter, int is_quoted)
{
	int		pipe_fds[2];
	pid_t	pid;
	char	*processed_delimiter;

	if (pipe(pipe_fds) == -1)
		return (ft_error(data, "pipe"), -1);
	processed_delimiter = ft_strdup(delimiter);
	if (!processed_delimiter)
		return (ft_error(data, "malloc"), close_pipe(data, pipe_fds), -1);
	if (is_quoted)
		process_quoted_delimiter(data, &processed_delimiter);
	pid = fork();
	if (pid == -1)
		return (ft_error(data, "fork"), free(processed_delimiter),
			close_pipe(data, pipe_fds), -1);
	if (pid == 0)
	{
		set_signal(SIGINT, SIG_DFL);
		set_signal(SIGQUIT, SIG_IGN);
		handle_heredoc_child(data, pipe_fds, processed_delimiter, is_quoted);
		return (-1);
	}
	free(processed_delimiter);
	return (handle_heredoc_parent(data, pipe_fds, pid));
}

int	handle_heredoc_redirection(t_data *data, t_token *token,
	int *heredoc_fd)
{
	int		is_quoted;

	is_quoted = 0;
	if (ft_strchr(token->str, '\'') || ft_strchr(token->str, '"'))
		is_quoted = 1;
	if (*heredoc_fd != -1)
		close(*heredoc_fd);
	*heredoc_fd = handle_heredoc(data, token->str, is_quoted);
	if (*heredoc_fd == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
