/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rough_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/25 19:07:34 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_make_test_strarr(char *str);

int	main(int argc, char *argv[], char *envp[])
{
	char	*here;
	t_env	*env;
	pid_t	pid;

	here = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	(void)argc;
	env = ft_calloc(1, sizeof(t_env));
	env->envp = ft_strarray_mapi(envp, ft_strdup);
	ft_echo("print this string with newline", false);
	ft_echo("print this string without newline", true);
	ft_echo("print this string \n with newline", false);
	ft_echo(NULL, true);
	ft_echo(NULL, false);
	here = getcwd(here, BUFFER_SIZE);
	ft_pwd();
	ft_cd("tests/testdir");
	ft_pwd();
	ft_printf("______\n");
	chdir(here);
	pid = fork();
	if (pid == 0)
		ft_cd("tests/testdir_readonly");
	pid = fork();
	if (pid == 0)
		ft_cd("tests/testdir_no_right");
	pid = fork();
	if (pid == 0)
		ft_cd("tests/rough_tests.c");
	pid = fork();
	if (pid == 0)
		ft_cd("lalala");
	ft_print_array(envp, true);
	ft_export(ft_make_test_strarr(argv[1]), env);
	ft_print_array(envp, true);
	ft_export(ft_make_test_strarr(argv[2]), env);
	ft_export(ft_make_test_strarr(argv[3]), env);
	pid = fork();
	if (pid == 0)
		ft_export(ft_make_test_strarr(argv[4]), env);
	ft_export(ft_make_test_strarr(argv[5]), env);
	ft_export(ft_make_test_strarr(argv[6]), env);
	return (0);
}

char	**ft_make_test_strarr(char *str)
{
	char	**test_arr;

	test_arr = ft_calloc(2, sizeof(char *));
	test_arr[0] = str;
	test_arr[1] = NULL;
	return (test_arr);
}
