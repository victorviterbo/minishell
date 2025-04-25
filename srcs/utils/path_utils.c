/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:24:23 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/25 19:41:57 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isdirectory(char *path)
{
	DIR	*directory;

	directory = opendir(path);
	if (directory == NULL)
	{
		closedir(directory);
		return (false);
	}
	else
	{
		closedir(directory);
		return (true);
	}
}

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
		return (data->exit_status);
	}
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

char	*get_absolute_path_backup_method(t_data *data, char *path)
{
	char	*current_path;
	char	*absolute_path;

	ft_fprintf(STDERR_FILENO, "cd: error retrieving current directory: "
		"getcwd: cannot access parent directories: %s\n",
		strerror(data->exit_status));
	data->exit_status = EXIT_SUCCESS;
	current_path = get_var(data, "PWD");
	if (!current_path)
		return (ft_error(data, "cd: PWD not set"),
			data->exit_status = EXIT_FAILURE, NULL);
	current_path = ft_strjoin_ip(current_path, "/", FREE_S1);
	if (!current_path)
		return (ft_error(data, "cd: memory allocation failed"), NULL);
	absolute_path = ft_strjoin_ip(current_path, path, FREE_S1);
	if (!absolute_path)
		return (ft_error(data, "cd: memory allocation failed"), NULL);
	return (absolute_path);
}

char	*get_absolute_path(t_data *data, char *path)
{
	char	*absolute_path;

	if (!path)
		return (ft_error(data, "cd: empty path"), NULL);
	if (path[0] == '/')
	{
		absolute_path = ft_strdup(path);
		if (!absolute_path)
			return (ft_error(data, "cd: memory allocation failed"), NULL);
		return (absolute_path);
	}
	absolute_path = ft_get_current_path(data);
	if (absolute_path)
		return (absolute_path);
	return (get_absolute_path_backup_method(data, path));
}
