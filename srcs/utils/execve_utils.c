/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:39:31 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/27 11:04:45 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_path_auth(t_data *data, char *path)
{
	char	*parent_path;

	errno = EXIT_SUCCESS;
	if (ft_strchr(path, '/') == NULL)
		return (EXIT_SUCCESS);
	if (path[ft_strlen(path)] == '/')
		return (EXIT_FAILURE);
	parent_path = ft_substr(path, 0, ft_strrchr(path, '/') - path + 1);
	if (!parent_path)
		return (ft_error(data, "redirection: memory allocaton failed"),
			EXIT_FAILURE);
	if (access(parent_path, W_OK) != 0)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", SHELL_NAME, path,
			strerror(errno));
		data->exit_status = EXIT_FAILURE;
		free(parent_path);
		return (data->exit_status);
	}
	free(parent_path);
	return (EXIT_SUCCESS);
}

int	check_file_error(t_data *data, char *path, char type)
{
	if (access(path, F_OK) != 0)
	{
		if (type == 'w')
			return (check_path_auth(data, path));
		ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", SHELL_NAME, path,
			strerror(errno));
		data->exit_status = EXIT_FAILURE;
		return (data->exit_status);
	}
	if (type == 'w' && access(path, W_OK))
		return (EXIT_SUCCESS);
	else if ((type == 'w' && access(path, W_OK) != 0)
		|| (type == 'r' && access(path, R_OK) != 0))
	{
		ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", SHELL_NAME, path,
			strerror(errno));
		data->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	exec_path_preprocess(t_data *data, char **args)
{
	get_exec_path(data, args);
	if (!data->exit_status && ft_isdirectory(args[0]))
	{
		data->exit_status = 126;
		ft_fprintf(STDERR_FILENO,
			"%s: %s: Is a directory\n", SHELL_NAME, args[0]);
	}
	if (data->exit_status)
	{
		free_all(data);
		if (args)
			ft_free_array((void **)args, ft_arrlen(args));
		exit (data->exit_status);
	}
}
