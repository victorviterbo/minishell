/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:07:54 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/15 17:20:25 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_data *data, char *path);
char	*get_absolute_path(t_data *data, char *path);

void	ft_cd(t_data *data, char *path)
{
	char	*abspath;
	char	*pwd;

	if (!data)
		return (ft_error(data, "cd: no env found"));
	if (!path)
		return (ft_error(data, "cd: no path given"));
	abspath = get_absolute_path(data, path);
	if (data->exit_status)
		return ;
	if (access(abspath, R_OK) == -1 || chdir(abspath) == -1)
		return (ft_error(data, ft_strjoin("cd: ", path)));
	pwd = ft_strjoin_ip("OLDPWD=", get_var(data, "PWD"), FREE_S2);
	if (!pwd)
		return (ft_error(data, "cd: error in setting OLDPWD"));
	new_var(data, pwd);
	free(pwd);
	if (data->exit_status)
		return ;
	pwd = ft_strjoin_ip("PWD=", ft_get_current_path(data), FREE_S2);
	if (!pwd)
		return (ft_error(data, "cd: error in setting PWD"));
	new_var(data, pwd);
	return (free(pwd), free(abspath));
}

char	*get_absolute_path(t_data *data, char *path)
{
	char	*current_path;
	char	*absolute_path;

	if (!path)
		return (ft_error(data, "cd: no env found"), NULL);
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

/*
if we want to handle the checking of whether or not the file we are trying to cd
to is a directory or not we should include this code in ft_cd. Otherwise,
chdir do it by itself...

	struct stat	path_stat;

	if (stat(abspath, &path_stat))
		ft_perror_exit(ft_strjoin("cd", path));
	if (S_ISDIR(path_stat.st_mode) == 0)
		ft_custom_error_exit(ft_strjoin(ft_strjoin("cd: ", path),
				": Not a directory"));
*/
