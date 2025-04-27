/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:24:23 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/27 21:00:13 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isdirectory(char *path)
{
	DIR	*directory;

	if (!path)
		return (false);
	if (access(path, F_OK) != 0)
		return (false);
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

int	init_pwd_oldpwd(t_data *data)
{
	char	*pwd;

	pwd = get_var(data, "PWD");
	if (data->exit_status != EXIT_SUCCESS)
		return (data->exit_status);
	if (pwd)
		free(pwd);
	else
	{
		if (ft_update_pwd(data, NULL))
			return (data->exit_status);
		new_var(data, "OLDPWD");
		if (data->exit_status != EXIT_SUCCESS)
			return (data->exit_status);
	}
	return (EXIT_SUCCESS);
}
