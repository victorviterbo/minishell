/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 01:51:13 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/27 01:29:19 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_std_streams(t_data *data)
{
	data->saved_streams[0] = dup(STDIN_FILENO);
	if (data->saved_streams[0] == -1)
		return (ft_error(data, "dup"), data->exit_status);
	data->saved_streams[1] = dup(STDOUT_FILENO);
	if (data->saved_streams[1] == -1)
	{
		close(data->saved_streams[0]);
		data->saved_streams[0] = -1;
		return (ft_error(data, "dup"), data->exit_status);
	}
	return (EXIT_SUCCESS);
}

int	restore_std_streams(t_data *data, int saved_streams[2])
{
	if (dup2(saved_streams[0], STDIN_FILENO) == -1)
		return (ft_error(data, "dup2"), data->exit_status);
	if (dup2(saved_streams[1], STDOUT_FILENO) == -1)
		return (ft_error(data, "dup2"), data->exit_status);
	return (EXIT_SUCCESS);
}

static int	redirect(t_data *data, int redi_fd, char *path, int flags)
{
	int	fd;

	fd = open(path, flags, 0664);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", SHELL_NAME, path,
			strerror(errno));
		data->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	if (dup2(fd, redi_fd) == -1)
		ft_error(data, "dup2");
	close(fd);
	return (data->exit_status);
}

int	handle_stdin_redirection(t_data *data, t_token *token)
{
	char	**parsed;
	int		len;

	parsed = parse_str(data, token->str, STDIN);
	if (!parsed)
		return (EXIT_FAILURE);
	len = ft_arrlen(parsed);
	if (len == 0 && token->str[0] == '$')
		return (handle_ambiguous_redirect(data, token, parsed));
	if (len == 0)
		return (ft_free_array((void **)parsed, len),
			redirect(data, STDIN_FILENO, token->str, O_RDONLY));
	if (len > 1 || ft_strlen(parsed[0]) == 0)
		return (handle_ambiguous_redirect(data, token, parsed));
	if (check_file_error(data, parsed[0], 'r') != EXIT_SUCCESS
		|| redirect(data, STDIN_FILENO, parsed[0], O_RDONLY))
		return (ft_free_array((void **)parsed, len), EXIT_FAILURE);
	return (ft_free_array((void **)parsed, len), EXIT_SUCCESS);
}

int	handle_stdout_redirection(t_data *data, t_token *token, int append)
{
	char	**parsed;
	int		len;
	int		flags;

	flags = !append * (O_CREAT | O_WRONLY | O_TRUNC)
		+ append * (O_CREAT | O_WRONLY | O_APPEND);
	parsed = parse_str(data, token->str, STDOUT);
	if (!parsed)
		return (EXIT_FAILURE);
	len = ft_arrlen(parsed);
	if (len == 0 && token->str[0] == '$')
		return (handle_ambiguous_redirect(data, token, parsed));
	if (len == 0)
	{
		ft_free_array((void **)parsed, len);
		if (redirect(data, STDOUT_FILENO, token->str, flags))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (len > 1 || ft_strlen(parsed[0]) == 0)
		return (handle_ambiguous_redirect(data, token, parsed));
	if (check_file_error(data, parsed[0], 'w') != EXIT_SUCCESS
		|| redirect(data, STDOUT_FILENO, parsed[0], flags))
		return (ft_free_array((void **)parsed, len), EXIT_FAILURE);
	return (ft_free_array((void **)parsed, len), EXIT_SUCCESS);
}
