/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:11:37 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/12 20:05:45 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	test_execve(t_data *data, char *str, int expected);

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	init_env(data, envp);
	test_execve(data, "/bin/cat miniprint.c", 0);
	test_execve(data, "cd not_a_dir", 1);
	test_execve(data, "cat miniprint.c", 0);
	test_execve(data, "grep -A3 -B1 tests test_env.c", 0);
	test_execve(data, "sleep 0.1", 0);
	test_execve(data, "NULL", 1);
	test_execve(data, "unkown command", 1);
	test_execve(data, "./segfault_test", 1);
	test_execve(data, "./miniprint", 0);
	test_execve(data, "cat lalalala", 1);
	free_env(data);
	return (EXIT_SUCCESS);
}

static void	test_execve(t_data *data, char *str, int expected)
{
	pid_t	pid;
	char	**args;
	int		exit_status;

	pid = fork();
	if (pid == 0)
	{
		args = ft_split(str, ' ');
		ft_execve(data, args);
	}
	waitpid(pid, &(exit_status), 0);
	if ((int)(exit_status != 0) != expected)
		exit (EXIT_FAILURE);
	ft_printf("%s ok\n", str);
}
