/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 03:30:24 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/27 02:46:16 by vbronov          ###   ########.fr       */
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

int	create_tmp_heredoc_file(t_data *data, char **out_fname)
{
	static unsigned int	index;
	char				*filename;
	int					fd;

	while (TRUE)
	{
		filename = ft_utoa_base(++index, "0123456789");
		if (!filename)
			return (ft_error(data, "heredoc: malloc"), -1);
		filename = ft_strjoin_ip("/tmp/.heredoc_", filename, FREE_S2);
		if (!filename)
			return (ft_error(data, "heredoc: malloc"), -1);
		fd = open(filename, O_CREAT | O_RDWR | O_EXCL, 0600);
		if (fd >= 0)
			return (*out_fname = filename, fd);
		else if (errno != EEXIST)
		{
			ft_fprintf(STDERR_FILENO,
				"%s: %s: %s\n", SHELL_NAME, filename, strerror(errno));
			return (data->exit_status = EXIT_FAILURE, free(filename), -1);
		}
		free(filename);
	}
}

static int	handle_heredoc(t_data *data, char *delimiter, int is_quoted)
{
	int		fd;
	pid_t	pid;
	char	*processed_delimiter;
	char	*filename;

	fd = create_tmp_heredoc_file(data, &filename);
	if (fd == -1)
		return (-1);
	processed_delimiter = ft_strdup(delimiter);
	if (!processed_delimiter)
		return (ft_error(data, "malloc"), close(fd), free(filename), -1);
	if (is_quoted)
		process_quoted_delimiter(data, &processed_delimiter);
	pid = fork();
	if (pid == -1)
		return (ft_error(data, "fork"), free(processed_delimiter),
			close(fd), free(filename), -1);
	if (pid == 0)
	{
		free(filename);
		handle_heredoc_child(data, fd, processed_delimiter, is_quoted);
		return (-1);
	}
	free(processed_delimiter);
	return (handle_heredoc_parent(data, fd, pid, filename));
}

int	handle_heredoc_redirection(t_data *data, t_token *token, int *heredoc_fd)
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
