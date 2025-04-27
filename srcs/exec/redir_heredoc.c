/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 03:27:42 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/27 04:14:20 by vbronov          ###   ########.fr       */
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

void	handle_heredoc_child(t_data *data, int fd,
	char *delimiter, int is_quoted)
{
	char	*line;

	(set_signal(SIGINT, SIG_DFL), set_signal(SIGQUIT, SIG_IGN));
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
		ft_fprintf(fd, "%s\n", line);
		free(line);
	}
	free(delimiter);
	close(fd);
	free_all(data);
	exit(EXIT_SUCCESS);
}

int	handle_heredoc_parent(t_data *data, int fd, pid_t pid, char *filename)
{
	if (wait_pid(data, pid) != EXIT_SUCCESS)
	{
		ft_fprintf(STDERR_FILENO, "TESTER\n");
		close(fd);
		unlink(filename);
		free(filename);
		return (-1);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO,
			"%s: %s: %s\n", SHELL_NAME, filename, strerror(errno));
		data->exit_status = EXIT_FAILURE;
	}
	unlink(filename);
	free(filename);
	return (fd);
}
