/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:11:37 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/12 17:58:57 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

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
		args = ft_split("/bin/cat miniprint.c", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status != 0)
		return (EXIT_FAILURE);
	ft_printf("/bin/cat miniprint.c ok\n");
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
		args = ft_split("cat miniprint.c", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status != 0)
		return (EXIT_FAILURE);
	ft_printf("cat miniprint.c ok\n");
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("grep -A3 -B1 tests test_env.c", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status != 0)
		return (EXIT_FAILURE);
	ft_printf("grep -A3 -B1 tests test_env.c ok\n");
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("sleep 0.1", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status != 0)
		return (EXIT_FAILURE);
	ft_printf("sleep 0.1 ok\n");
	pid = fork();
	if (pid == 0)
	{
		ft_execve(data, NULL);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status == 0)
		return (EXIT_FAILURE);
	ft_printf("NULL ok\n");
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("unkown command", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status == 0)
		return (EXIT_FAILURE);
	ft_printf("unkown command ok\n");
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("./segfault_test", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status == 0)
		return (EXIT_FAILURE);
	ft_printf("segfault_test ok\n");
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("./miniprint", ' ');
		ft_printf("1\n");
		ft_print_array(args, true);
		ft_printf("%i\n", ft_arrlen(args));
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status != 0)
		return (EXIT_FAILURE);
	ft_printf("miniprint ok\n");
	pid = fork();
	if (pid == 0)
	{
		args = ft_split("cat lalalala", ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if (exit_status == 0)
		return (EXIT_FAILURE);
	ft_printf("cat lalalala ok\n");
	ft_printf("done !\n");
	ft_lstclear(data->envp, free_var);
	free(data->envp);
	ft_free_array((void **)data->env_arr, ft_arrlen(data->env_arr));
	free(data);
	return (EXIT_SUCCESS);
}
