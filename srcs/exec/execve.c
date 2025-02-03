/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:10:47 by madelmen          #+#    #+#             */
/*   Updated: 2025/02/03 17:39:39 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_execve(t_data *data, char **args);
char	*find_exec(char *path_list, char *exec);

int	ft_execve(t_data *data, char **args)
{
	char	**env_arr;
	char	*path;
	char	*path_exec;

	env_arr = env_to_arr(data);
	if (!env_arr || !*env_arr)
		ft_print_error("memory allocation failed");
	path = get_var(data, "PATH");
	if (!path)
		ft_print_error("No path variable found");
	path_exec = find_exec(path, args[0]);
	free(path);
	if (!path_exec)
		ft_print_error("Could not find executable");
	if (execve(path_exec, args, env_arr) == -1)
		ft_print_error("Calling of executable failed !");
	return (EXIT_SUCCESS);
}

char	*find_exec(char *path_list, char *exec)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (access(exec, X_OK) == 0)
		return (ft_strdup(exec));
	paths = ft_split(path_list, ':');
	if (!paths || !*paths)
		ft_print_error("execve: memory allocation failed");
	i = 0;
	exec = ft_strjoin_ip("/", exec, FREE_S2);
	while (paths[i])
	{
		full_path = ft_strjoin_ip(paths[i], exec, FREE_S1);
		if (!full_path)
			ft_print_error("execve: memory allocation failed");
		if (access(full_path, X_OK) == 0)
			return (ft_free_array((void **)paths, ft_arrlen(paths)),
				full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
