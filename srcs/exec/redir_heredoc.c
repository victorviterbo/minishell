/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 03:27:42 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/20 03:30:38 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_eof_message(char *delimiter)
{
	ft_fprintf(STDERR_FILENO,
		"minishell: warning: here-document delimited by end-of-file"
		" (wanted `%s')\n", delimiter);
}

static void	handle_child_expansion(t_data *data, char **line, int is_quoted)
{
	int		*isescaped;
	char	*expanded;

	if (is_quoted)
		return ;
	isescaped = ft_calloc(ft_strlen(*line) + 1, sizeof(int));
	if (!isescaped)
		return ;
	expanded = expand_var(data, *line, isescaped);
	if (expanded)
	{
		free(*line);
		*line = expanded;
	}
	free(isescaped);
}

void	handle_heredoc_child(t_data *data, int *pipe_fds,
	char *delimiter, int is_quoted)
{
	char	*line;

	close(pipe_fds[0]);
	while (TRUE)
	{
		line = readline("> ");
		if (!line)
		{
			heredoc_eof_message(delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		handle_child_expansion(data, &line, is_quoted);
		ft_fprintf(pipe_fds[1], "%s\n", line);
		free(line);
	}
	free(delimiter);
	close(pipe_fds[1]);
	free_all(data);
	exit(EXIT_SUCCESS);
}

int	handle_heredoc_parent(t_data *data, int *pipe_fds, pid_t pid)
{
	close(pipe_fds[1]);
	if (wait_pid(data, pid) != EXIT_SUCCESS)
	{
		close(pipe_fds[0]);
		return (-1);
	}
	return (pipe_fds[0]);
}
