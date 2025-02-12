/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:10:47 by madelmen          #+#    #+#             */
/*   Updated: 2025/02/12 13:00:34 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_execve(t_data *data, char **args);
char	*find_exec(char *path_list, char *exec);

int	ft_execve(t_data *data, char **args)
{
	char	*path;
	char	*path_exec;

	if (!args)
		ft_print_error("execve: empty command");
	path = get_var(data, "PATH");
	if (!path)
		ft_print_error("execve: no path variable found");
	path_exec = find_exec(path, args[0]);
	free(path);
	if (!path_exec)
		ft_print_error("execve: could not find executable");
	if (execve(path_exec, args, data->env_arr) == -1)
		ft_print_error("execve: calling of executable failed !");
	return (EXIT_SUCCESS);
}

char	*find_exec(char *path_list, char *exec)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!exec)
		ft_print_error("execve: no executable given");
	if (access(exec, X_OK) == 0)
		return (ft_strdup(exec));
	paths = ft_split(path_list, ':');
	if (!paths)
		ft_print_error("execve: memory allocation failed");
	i = 0;
	exec = ft_strjoin("/", exec);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], exec);
		if (!full_path)
			ft_print_error("execve: memory allocation failed");
		if (access(full_path, X_OK) == 0)
			return (ft_free_array((void **)paths, ft_arrlen(paths)), free(exec),
				full_path);
		free(full_path);
		i++;
	}
	return (free(exec), NULL);
}
