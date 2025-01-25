/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:07:54 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/25 19:07:34 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(char *path);
char	*get_absolute_path(char *path);

int	ft_cd(char *path)
{
	char		*abspath;

	abspath = get_absolute_path(path);
	if (access(abspath, R_OK) == -1)
		ft_perror_exit(ft_strjoin("Minishell: cd: ", path));
	if (chdir(abspath) == -1)
		ft_perror_exit(ft_strjoin("Minishell: cd: ", path));
	return (free(abspath), EXIT_SUCCESS);
}

char	*get_absolute_path(char *path)
{
	char	*current_path;
	char	*absolute_path;

	if (path[0] == '/')
		return (ft_strdup(path));
	current_path = ft_strjoin_ip(ft_get_current_path(), "/", 1);
	absolute_path = ft_strjoin(current_path, path);
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