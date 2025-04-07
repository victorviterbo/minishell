/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:07:54 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/07 13:11:42 by vviterbo         ###   ########.fr       */
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
	current_path = ft_strjoin_ip(ft_get_current_path(data), "/", FREE_S1);
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
		return (ft_error(data, "cd: PWD not set"), EXIT_FAILURE);
	pwd = ft_strjoin_ip("OLDPWD=", pwd, FREE_S2);
	if (!pwd)
		return (ft_error(data, "cd: memory allocation failed"), EXIT_FAILURE);
	new_var(data, pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

static int	ft_update_pwd(t_data *data)
{
	char	*pwd;

	pwd = ft_strjoin_ip("PWD=", ft_get_current_path(data), FREE_S2);
	if (!pwd)
	{
		ft_error(data, "cd: memory allocation failed");
		return (EXIT_FAILURE);
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
	{
		ft_error(data, "cd: too many arguments");
		return (EXIT_FAILURE);
	}
	path = handle_special_paths(data, args[1]);
	if (!path)
		return (EXIT_FAILURE);
	abspath = get_absolute_path(data, path);
	free(path);
	if (data->exit_status)
		return (EXIT_FAILURE);
	if (access(abspath, R_OK) == -1 || chdir(abspath) == -1)
	{
		ft_error(data, "cd");
		free(abspath);
		return (EXIT_FAILURE);
	}
	free(abspath);
	if (ft_update_oldpwd(data) || ft_update_pwd(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
