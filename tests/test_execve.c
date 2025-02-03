/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:11:37 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/03 17:29:42 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	char	**args;
	pid_t	pid;
	int		exit_status;

	data = ft_calloc(1, sizeof(t_data));
	init_env(data, envp);
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("ls -la /Users/vviterbo/Desktop/42", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status != 0)
		return (EXIT_FAILURE);
	ft_free_array((void **)args, ft_arrlen(args));
	
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("cd lalala", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status == 0)
		return (EXIT_FAILURE);
	
	if (ft_execve(data, args) != 0)
		return (EXIT_FAILURE);
	ft_free_array((void **)args, ft_arrlen(args));
	
	args = ft_split("ls -la /Users/vviterbo/Desktop/42", ' ');
	if (ft_execve(data, args) != 0)
		return (EXIT_FAILURE);
	ft_free_array((void **)args, ft_arrlen(args));
	
	args = ft_split("ls -la /Users/vviterbo/Desktop/42", ' ');
	if (ft_execve(data, args) != 0)
		return (EXIT_FAILURE);
	ft_free_array((void **)args, ft_arrlen(args));
	

int	monitor_process(int pid)
{
	int	exit_status;
	int	waitpid_status;
	
	waitpid_status = ;
		if (waitpid_status[1] == 0)
			waitpid_status[1] = waitpid(pid[1], &(exit_status[1]), WNOHANG);
		if (waitpid_status[0] == -1)
			ft_perror_exit("waitpid on sender exception in parent process");
		if (waitpid_status[1] == -1)
			ft_perror_exit("waitpid on receiver exception in parent process");
	}
	if (exit_status[1] && exit_status[1] % 256 == 0)
		exit_status[1] = 1;
	return (exit_status[1]);
}