/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/28 18:03:07 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_make_test_strarr(char *str);

int	main(int argc, char *argv[], char *envp[])
{
	char	*here;
	t_data	*data;
	pid_t	pid;

	(void)argc;
	(void)argv;
	here = ft_get_current_path();
	data = ft_calloc(1, sizeof(t_data));
	init_env(data, envp);
	ft_pwd();
	if (ft_cd(data, "testdir") != 0)
		return (EXIT_FAILURE);
	ft_pwd();
	ft_cd(data, here);
	pid = fork();
	if (pid == 0)
		if (ft_cd(data, "testdir_readonly") == 0)
			return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		if (ft_cd(data, "testdir_no_right") == 0)
			return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		if (ft_cd(data, "test_cd_pwd.c") == 0)
			return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		if (ft_cd(data, "lalala") == 0)
			return (EXIT_FAILURE);
	if (ft_cd(data, "/Users/vviterbo/Desktop/42/minishell") != 0)
		return (EXIT_FAILURE);
	if (ft_cd(data, "/Users/vviterbo/Desktop/42/minishell/") != 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		if (ft_cd(data, "/Users/vviterbo/Desktop/42/not_a_folder") == 0)
			return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		if (ft_cd(data, "/Users/vviterbo/Desktop/42/not_a_folder/") == 0)
			return (EXIT_FAILURE);
	free(here);
	ft_lstclear(data->envp, free_var);
	free(data->envp);
	free(data);
	return (EXIT_SUCCESS);
}
