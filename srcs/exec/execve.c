/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:10:47 by madelmen          #+#    #+#             */
/*   Updated: 2025/04/01 00:34:00 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_data *data, char **args);
char	*find_exec(t_data *data, char *path_list, char *exec);
char	*search_exec(t_data *data, char *path_list, char *exec);

void	ft_execve(t_data *data, char **args)
{
	char	*path;
	char	*path_exec;

	if (!args)
		return (ft_error(data, "execve: empty command"));
	path = get_var(data, "PATH");
	if (data->exit_status)
		return ;
	path_exec = find_exec(data, path, args[0]);
	free(path);
	if (data->exit_status)
		return ;
	if (execve(path_exec, args, data->env_arr) == -1)
		return (ft_error(data, "execve: calling of executable failed !"));
	return ;
}

char	*find_exec(t_data *data, char *path_list, char *exec)
{
	char	*full_path;

	if (!exec)
		return (ft_error(data, "execve: no executable given"), NULL);
	if (access(exec, X_OK) == 0)
	{
		full_path = ft_strdup(exec);
		if (!full_path)
			return (ft_error(data, "execve: memory allocation failed"), NULL);
		return (full_path);
	}
	return (search_exec(data, path_list, exec));
}

char	*search_exec(t_data *data, char *path_list, char *exec)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = ft_split(path_list, ':');
	if (!paths)
		return (ft_error(data, "execve: memory allocation failed"), NULL);
	i = 0;
	exec = ft_strjoin("/", exec);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], exec);
		if (!full_path)
			return (ft_error(data, "execve: memory allocation failed"), NULL);
		if (access(full_path, X_OK) == 0)
			return (ft_free_array((void **)paths, ft_arrlen(paths)), free(exec),
				full_path);
		free(full_path);
		i++;
	}
	return (free(exec), ft_error(data, "execve: could not find executable"),
		NULL);
}

void	init_builtin(t_data *data)
{
	data->builtins[0] = (t_builtin){"cd", ft_cd};
	data->builtins[1] = (t_builtin){"echo", ft_echo};
	data->builtins[2] = (t_builtin){"env", ft_env};
	data->builtins[3] = (t_builtin){"exit", ft_exit};
	data->builtins[4] = (t_builtin){"export", ft_export};
	data->builtins[5] = (t_builtin){"pwd", ft_pwd};
	data->builtins[6] = (t_builtin){"unset", ft_unset};
	data->builtins[7] = (t_builtin){NULL, NULL};
}
