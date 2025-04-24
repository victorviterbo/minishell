/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:07:54 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/24 13:41:00 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_special_paths(t_data *data, char *path)
{
	char	*special_path;

	if (!path || !ft_strcmp(path, "~"))
	{
		special_path = get_var(data, "HOME");
		if (!special_path)
			return (ft_error(data, "cd: HOME not set"), NULL);
		return (special_path);
	}
	if (!ft_strcmp(path, "-"))
	{
		special_path = get_var(data, "OLDPWD");
		if (!special_path)
			return (ft_error(data, "cd: OLDPWD not set"), NULL);
		return (special_path);
	}
	special_path = ft_strdup(path);
	if (!special_path)
		return (ft_error(data, "cd: memory allocation failed"), NULL);
	return (special_path);
}

char	*get_absolute_path(t_data *data, char *path)
{
	char	*current_path;
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

static int	ft_update_oldpwd(t_data *data)
{
	char	*pwd;

	pwd = get_var(data, "PWD");
	if (!pwd)
	{
		ft_error(data, "cd: PWD not set");
		data->exit_status = EXIT_FAILURE;
		return (data->exit_status);
	}
	pwd = ft_strjoin_ip("OLDPWD=", pwd, FREE_S2);
	if (!pwd)
	{
		ft_error(data, "cd: memory allocation failed");
		data->exit_status = EXIT_FAILURE;
		return (data->exit_status);
	}
	new_var(data, pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

static int	ft_update_pwd(t_data *data, const char *abspath)
{
	char	*pwd;

	pwd = ft_strjoin("PWD=", abspath);
	if (!pwd)
	{
		ft_error(data, "cd: memory allocation failed");
		data->exit_status = EXIT_FAILURE;
		return (data->exit_status);
	}
	new_var(data, pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_data *data, char **args, int argc)
{
	char	*abspath;
	char	*path;

	if (argc > 2)
		return (ft_error(data, "cd: too many arguments"), EXIT_FAILURE);
	path = handle_special_paths(data, args[1]);
	if (!path)
		return (data->exit_status = EXIT_FAILURE, EXIT_FAILURE);
	if (access(path, R_OK) == -1 || chdir(path) == -1)
	{
		ft_fprintf(STDERR_FILENO, "%s: cd: %s: %s\n",
			SHELL_NAME, path, strerror(errno));
		return (free(path), data->exit_status = EXIT_FAILURE, EXIT_FAILURE);
	}
	abspath = get_absolute_path(data, path);
	free(path);
	if (ft_update_oldpwd(data) || ft_update_pwd(data, abspath))
		return (free(abspath), EXIT_FAILURE);
	return (free(abspath), EXIT_SUCCESS);
}
