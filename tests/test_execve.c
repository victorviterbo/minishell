/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:11:37 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/06 19:07:08 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	char	**args;
	pid_t	pid;
	int		exit_status;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	init_env(data, envp);
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("/bin/cat ../srcs/exec/cd.c", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status != 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("cd not_a_dir", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status == 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("cat ../srcs/exec/env.c", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status != 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("grep -A3 -B1 minishell test_env.c", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status != 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("sleep 0.1", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status != 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		ft_execve(data, NULL);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status == 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("unkown command", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status == 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("./segfault_test", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status == 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("./miniprint", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status != 0)
		return (EXIT_FAILURE);
	ft_printf("done !\n");
	ft_lstclear(data->envp, free_var);
	free(data->envp);
	free(data);
	return (EXIT_SUCCESS);
}
