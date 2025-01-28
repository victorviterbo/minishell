/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:07:54 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/28 20:32:56 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(t_data *data, char *path);
char	*get_absolute_path(char *path);

int	ft_cd(t_data *data, char *path)
{
	char	*abspath;
	char	*pwd;
	int		success;

	abspath = get_absolute_path(path);
	if (access(abspath, R_OK) == -1)
		ft_perror_exit(ft_strjoin("Minishell: cd: ", path));
	if (chdir(abspath) == -1)
		ft_perror_exit(ft_strjoin("Minishell: cd: ", path));
	pwd = ft_strjoin_ip("OLDPWD=", get_var(data, "PWD"), FREE_S2);
	if (!pwd)
		ft_custom_error_exit("Minishell: cd: error in setting OLDPWD");
	success = new_var(data->envp, pwd);
	free(pwd);
	pwd = ft_strjoin_ip("PWD=", ft_get_current_path(), FREE_S2);
	if (!pwd)
		ft_custom_error_exit("Minishell: cd: error in setting PWD");
	success += new_var(data->envp, pwd);
	return (free(pwd), free(abspath), success);
}

char	*get_absolute_path(char *path)
{
	char	*current_path;
	char	*absolute_path;

	if (path[0] == '/')
		return (ft_strdup(path));
	current_path = ft_strjoin_ip(ft_get_current_path(), "/", FREE_S1);
	absolute_path = ft_strjoin_ip(current_path, path, FREE_S1);
	return (absolute_path);
}

/*
if we want to handle the checking of whether or not the file we are trying to cd
to is a directory or not we should include this code in ft_cd. Otherwise,
chdir do it by itself...

	struct stat	path_stat;

	if (stat(abspath, &path_stat))
		ft_perror_exit(ft_strjoin("Minishell: cd", path));
	if (S_ISDIR(path_stat.st_mode) == 0)
		ft_custom_error_exit(ft_strjoin(ft_strjoin("Minishell: cd: ", path),
				": Not a directory"));
*/