/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/26 13:45:43 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_make_test_strarr(char *str);

int	main(int argc, char *argv[], char *envp[])
{
	char	*here;
	t_env	*env;
	pid_t	pid;

	(void)argc;
	chdir(here);
	env = ft_calloc(1, sizeof(t_env));
	env->envp = ft_strarray_mapi(envp, ft_strdup);
	ft_print_array(envp, true);
	ft_export(ft_make_test_strarr("VAR1=test1"), env);
	ft_print_array(envp, true);
	ft_export(ft_make_test_strarr("VAR2=test=2"), env);
	ft_export(ft_make_test_strarr("VAR1="), env);
	pid = fork();
	if (pid == 0)
		ft_export(ft_make_test_strarr("=test1"), env);
	ft_export(ft_make_test_strarr("VAR2+=lala"), env);
	ft_export(ft_make_test_strarr("VAR1=lili"), env);
	ft_export(ft_split("VAR3=3 VAR4=4 VAR5=5", ' '), env);
	ft_export(ft_split("VAR3=3 =4 VAR5=5", ' '), env);
	return (0);
}

static char	**ft_make_test_strarr(char *str)
{
	char	**test_arr;

	test_arr = ft_calloc(2, sizeof(char *));
	test_arr[0] = str;
	test_arr[1] = NULL;
	return (test_arr);
}
