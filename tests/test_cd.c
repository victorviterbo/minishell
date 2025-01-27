/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/27 14:41:22 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_make_test_strarr(char *str);

int	main(int argc, char *argv[], char *envp[])
{
	char	*here;
	pid_t	pid;

	(void)argc;
	(void)argv;
	(void)envp;
	here = ft_get_current_path();
	ft_pwd();
	ft_cd("testdir");
	ft_pwd();
	ft_cd(here);
	pid = fork();
	if (pid == 0)
		ft_cd("testdir_readonly");
	pid = fork();
	if (pid == 0)
		ft_cd("testdir_no_right");
	pid = fork();
	if (pid == 0)
		ft_cd("test_cd.c");
	pid = fork();
	if (pid == 0)
		ft_cd("lalala");
	return (0);
}
