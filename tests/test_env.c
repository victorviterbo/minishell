/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/27 16:53:33 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_make_test_strarr(char *str);

int	main(int argc, char *argv[], char *envp[])
{
	char	*here;
	t_data	*data;
	pid_t	pid;
	char	*value;

	(void)argc;
	(void)argv;
	chdir(here);
	data = ft_calloc(1, sizeof(t_data));
	init_env(data, envp);
	ft_export(data, ft_make_test_strarr("VAR1=test1"));
	value = get_var(data, "VAR1");
	if (ft_strcmp(value , "test1"))
		return (1);
	free(value);
	ft_env(data);
	ft_unset(data, ft_make_test_strarr("VAR1"));
	value = get_var(data, "VAR1");
	if (ft_strcmp(value , ""))
		return (1);
	ft_export(data, ft_make_test_strarr("VAR2=test=2"));
	value = get_var(data, "VAR2");
	if (ft_strcmp(value , "test=2"))
		return (1);
	free(value);
	ft_env(data);
	ft_export(data, ft_make_test_strarr("VAR1="));
	value = get_var(data, "VAR1");
	if (ft_strcmp(value , ""))
		return (1);
	free(value);
	pid = fork();
	if (pid == 0)
	{
		ft_export(data, ft_make_test_strarr("=test1"));
		return (1);
	}
	ft_export(data, ft_make_test_strarr("VAR2+=lala"));
	value = get_var(data, "VAR2");
	if (ft_strcmp(value , "test=2lala"))
		return (1);
	free(value);
	ft_export(data, ft_make_test_strarr("VAR1=lili"));
	value = get_var(data, "VAR1");
	if (ft_strcmp(value , "lili"))
		return (1);
	free(value);
	ft_export(data, ft_split("VAR3=3 VAR4=4 VAR5=5", ' '));
	value = get_var(data, "VAR3");
	if (ft_strcmp(value , "3"))
		return (1);
	free(value);
	value = get_var(data, "VAR4");
	if (ft_strcmp(value , "4"))
		return (1);
	free(value);
	value = get_var(data, "VAR5");
	if (ft_strcmp(value , "5"))
		return (1);
	free(value);
	ft_export(data, ft_split("VAR3=6 =4 VAR5=7", ' '));
	ft_env(data);
	value = get_var(data, "VAR3");
	if (ft_strcmp(value , "6"))
		return (1);
	free(value);
	value = get_var(data, "VAR5");
	if (ft_strcmp(value , "7"))
		return (1);
	free(value);
	ft_unset(data, ft_make_test_strarr("NOT_A_VAR"));
	ft_env(data);
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
