/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:10:47 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/27 16:28:11 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exec_path(t_data *data, char **out_path, char **args)
{
	char	*path_list;

	if (!args || !args[0] || args[0][0] == '/' || !ft_strncmp(args[0], "./", 2)
		|| !ft_strncmp(args[0], "../", 3))
	{
		*out_path = ft_strdup(args[0]);
		if (!*out_path)
			return (ft_error(data, "execve: memory allocation failed"));
		return ;
	}
	if (!ft_strcmp(args[0], "."))
		return (error_execve_format(data));
	path_list = get_var(data, "PATH");
	if (!path_list)
		return ;
	*out_path = find_exec(data, path_list, args[0]);
	free(path_list);
	if (data->exit_status)
		return ;
	if (!out_path)
	{
		data->exit_status = 127;
		ft_fprintf(STDERR_FILENO, "%s: command not found\n", args[0]);
		return ;
	}
}

char	*find_exec(t_data *data, char *path_list, char *cmd)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = ft_split(path_list, ':');
	if (!paths)
		return (ft_error(data, "execve: memory allocation failed"), NULL);
	cmd = ft_strjoin("/", cmd);
	if (!cmd)
		return (ft_free_array((void **)paths, ft_arrlen(paths)),
			ft_error(data, "execve: memory allocation failed"), NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd);
		if (!full_path)
			return (ft_free_array((void **)paths, ft_arrlen(paths)),
				ft_error(data, "execve: memory allocation failed"), NULL);
		if (!ft_isdirectory(full_path) && access(full_path, X_OK) == 0)
			return (ft_free_array((void **)paths, ft_arrlen(paths)), free(cmd),
				full_path);
		free(full_path);
		i++;
	}
	return (ft_free_array((void **)paths, ft_arrlen(paths)), free(cmd), NULL);
}

int	ft_execve(t_data *data, char *path, char **args)
{
	if (access(path, X_OK) != 0)
	{
		if (errno == ENOENT)
			return (ft_error(data, path), data->exit_status = 127);
		else if (errno == EACCES)
			return (ft_error(data, path), data->exit_status = 126);
		else
			return (ft_error(data, path), data->exit_status);
	}
	update_env_arr(data);
	if (data->exit_status)
		return (data->exit_status);
	if (execve(path, args, data->env_arr) == -1)
	{
		data->exit_status = errno;
		if (errno == ENOENT)
			return (ft_error(data, path), data->exit_status = 127);
		else if (errno == EACCES)
			return (ft_error(data, path), data->exit_status = 126);
		else
			return (ft_error(data, path), data->exit_status);
	}
	return (EXIT_SUCCESS);
}

int	exec_non_builtin(t_data *data, char **args)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		path = NULL;
		exec_path_preprocess(data, &path, args);
		set_signal(SIGINT, SIG_DFL);
		set_signal(SIGQUIT, SIG_DFL);
		if (data->exit_status == EXIT_SUCCESS)
			ft_execve(data, path, args);
		if (path)
			free(path);
		ft_free_array((void **)args, ft_arrlen(args));
		free_all(data);
		exit (data->exit_status);
	}
	else if (pid < 0)
		return (ft_error(data, "fork"), data->exit_status);
	return (wait_pid(data, pid));
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
