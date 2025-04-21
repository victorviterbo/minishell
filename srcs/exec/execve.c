/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:10:47 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/21 21:15:57 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exec_path(t_data *data, char **args)
{
	char	*path_list;
	char	*full_path;

	if (!args || !args[0] || args[0][0] == '/' || !ft_strncmp(args[0], "./", 2)
		|| !ft_strncmp(args[0], "../", 3))
		return ;
	path_list = get_var(data, "PATH");
	if (data->exit_status)
		return ;
	full_path = find_exec(data, path_list, args[0]);
	free(path_list);
	if (data->exit_status)
		return ;
	if (!full_path)
	{
		data->exit_status = 127;
		ft_fprintf(STDERR_FILENO, "%s: command not found\n", SHELL_NAME,
			args[0]);
		return ;
	}
	free(args[0]);
	args[0] = full_path;
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
		if (access(full_path, X_OK) == 0)
			return (ft_free_array((void **)paths, ft_arrlen(paths)), free(cmd),
				full_path);
		free(full_path);
		i++;
	}
	return (ft_free_array((void **)paths, ft_arrlen(paths)), free(cmd), NULL);
}

int	ft_execve(t_data *data, char **args)
{
	if (access(args[0], X_OK) == -1)
	{
		if (errno == ENOENT)
			return (ft_error(data, args[0]), data->exit_status = 127);
		else if (errno == EACCES)
			return (ft_error(data, args[0]), data->exit_status = 126);
		else
			return (ft_error(data, args[0]), data->exit_status);
	}
	update_env_arr(data);
	if (data->exit_status)
		return (data->exit_status);
	if (execve(args[0], args, data->env_arr) == -1)
	{
		data->exit_status = errno;
		if (errno == ENOENT)
			return (ft_error(data, args[0]), data->exit_status = 127);
		else if (errno == EACCES)
			return (ft_error(data, args[0]), data->exit_status = 126);
		else
			return (ft_error(data, args[0]), data->exit_status);
	}
	return (EXIT_SUCCESS);
}

int	exec_non_builtin(t_data *data, char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		get_exec_path(data, args);
		set_signal(SIGINT, SIG_DFL);
		set_signal(SIGQUIT, SIG_DFL);
		if (data->exit_status == EXIT_SUCCESS)
			ft_execve(data, args);
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
