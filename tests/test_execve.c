/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:11:37 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 12:11:07 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	test_execve(t_data *data, char *str, bool expected_fail);

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	init_env(data, envp);
	test_execve(data, "/bin/cat miniprint.c", false);
	test_execve(data, "cd not_a_dir", true);
	test_execve(data, "cat miniprint.c", false);
	test_execve(data, "grep -A3 -B1 tests test_env.c", false);
	test_execve(data, "sleep 0.1", false);
	test_execve(data, NULL, true);
	test_execve(data, "unkown command", true);
	test_execve(data, "./segfault_test", true);
	test_execve(data, "./miniprint", false);
	test_execve(data, "cat lalalala", true);
	free_env(data);
	return (EXIT_SUCCESS);
}

static void	test_execve(t_data *data, char *str, bool expected_fail)
{
	pid_t	pid;
	char	**args;
	int		exit_status;

	pid = fork();
	if (pid == 0)
	{
		if (!str)
			ft_execve(data, NULL);
		else
		{
			args = ft_split(str, ' ');
			ft_execve(data, args);
		}
	}
	waitpid(pid, &(exit_status), 0);
	if ((exit_status == 0) == expected_fail)
		exit (EXIT_FAILURE);
	ft_printf("%s ok\n", str);
}
