/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:10:47 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/29 11:10:47 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		execute_external_cmd(t_data *data, char **args);
static void	handle_command_not_found(t_data *data, char **args);
static void	handle_child_process(char *path, char **args, t_data *data);
static void	handle_parent_process(pid_t pid, t_data *data);
static int	create_process(t_data *data, char *path, char **args);

static void	handle_command_not_found(t_data *data, char **args)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(args[0], 2);
	data->exit_status = 127;
}

static void	handle_child_process(char *path, char **args, t_data *data)
{
	execve(path, args, data->envp);
	exit(126);
}

static void	handle_parent_process(pid_t pid, t_data *data)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else
		data->exit_status = 1;
}

static int	create_process(t_data *data, char *path, char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		data->exit_status = 1;
		return (0);
	}
	if (pid == 0)
		handle_child_process(path, args, data);
	else
		handle_parent_process(pid, data);
	return (1);
}

void	execute_external_cmd(t_data *data, char **args)
{//je n alloue pas je ne FREE PAS
	char	**paths;

	if (!args || !args[0])
		return ;

	paths = ft_split(get_var(data, "PATH"), ':');
	if (!paths)
	{//perror("exec not found");
		handle_command_not_found(data, args);
		return ;
	}
	//while pour check all path access
	//strjoin pour path + name exec
	if (!create_process(data, paths, args))
	{
		free(paths);
		return ;
	}
	free(paths);
}
