/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/28 18:02:36 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_make_test_strarr(char *str);

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	pid_t	pid;
	char	*value1;
	char	*value2;
	char	*value3;
	char	*value4;
	char	*value5;
	char	*value6;
	char	**tmp_arr;
	char	**tmp_arr2;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	init_env(data, envp);
	tmp_arr = ft_make_test_strarr("VAR1");
	ft_unset(data, tmp_arr);
	free(tmp_arr);
	tmp_arr = ft_make_test_strarr("VAR2");
	ft_unset(data, tmp_arr);
	free(tmp_arr);
	tmp_arr = ft_make_test_strarr("VAR3");
	ft_unset(data, tmp_arr);
	free(tmp_arr);
	tmp_arr = ft_make_test_strarr("VAR4");
	ft_unset(data, tmp_arr);
	free(tmp_arr);
	tmp_arr = ft_make_test_strarr("VAR5");
	ft_unset(data, tmp_arr);
	free(tmp_arr);
	tmp_arr = ft_make_test_strarr("VAR1=test1");
	ft_export(data, tmp_arr);
	free(tmp_arr);
	value1 = get_var(data, "VAR1");
	if (ft_strcmp(value1 , "test1"))
		return (1);
	ft_env(data);
	free(value1);
	tmp_arr = ft_make_test_strarr("VAR1");
	ft_unset(data, tmp_arr);
	free(tmp_arr);
	value1 = get_var(data, "VAR1");
	if (*value1)
		return (1);
	free(value1);
	value1 = get_var(data, "VAR1");
	if (ft_strcmp(value1 , ""))
		return (1);
	free(value1);
	tmp_arr = ft_make_test_strarr("VAR2=test=2");
	ft_export(data, tmp_arr);
	free(tmp_arr);
	value1 = get_var(data, "VAR2");
	if (ft_strcmp(value1 , "test=2"))
		return (1);
	free(value1);
	ft_printf("\n\n---------------------------\n\n");
	ft_env(data);
	tmp_arr = ft_make_test_strarr("VAR1=");
	if (ft_export(data, tmp_arr) == 0)
		return (1);
	free(tmp_arr);
	value1 = get_var(data, "VAR1");
	if (ft_strcmp(value1 , ""))
		return (1);
	free(value1);
	pid = fork();
	if (pid == 0)
	{
		tmp_arr2 = ft_make_test_strarr("=test1");
		ft_export(data, tmp_arr2);
		free(tmp_arr2);
		return (1);
	}
	tmp_arr = ft_make_test_strarr("VAR2+=lala");
	ft_export(data, tmp_arr);
	free(tmp_arr);
	value1 = get_var(data, "VAR2");
	if (ft_strcmp(value1 , "test=2lala"))
		return (1);
	free(value1);
	tmp_arr = ft_make_test_strarr("VAR1=lili");
	ft_export(data, tmp_arr);
	free(tmp_arr);
	value1 = get_var(data, "VAR1");
	if (ft_strcmp(value1 , "lili"))
		return (1);
	free(value1);
	tmp_arr = ft_split("VAR3=3 VAR4=4 VAR5=5", ' ');
	ft_export(data, tmp_arr);
	ft_free_array((void **)tmp_arr, ft_arrlen(tmp_arr));
	value1 = get_var(data, "VAR3");
	if (ft_strcmp(value1 , "3"))
		return (1);
	free(value1);
	value1 = get_var(data, "VAR4");
	if (ft_strcmp(value1 , "4"))
		return (1);
	free(value1);
	value1 = get_var(data, "VAR5");
	if (ft_strcmp(value1 , "5"))
		return (1);
	free(value1);
	tmp_arr = ft_split("VAR3=6 =4 VAR5=7", ' ');
	ft_export(data, tmp_arr);
	ft_free_array((void **)tmp_arr, ft_arrlen(tmp_arr));
	ft_printf("\n\n---------------------------\n\n");
	ft_env(data);
	value1 = get_var(data, "VAR3");
	if (ft_strcmp(value1 , "6"))
		return (1);
	free(value1);
	value1 = get_var(data, "VAR5");
	if (ft_strcmp(value1 , "7"))
		return (1);
	free(value1);
	tmp_arr = ft_make_test_strarr("NOT_A_VAR");
	ft_unset(data, tmp_arr);
	free(tmp_arr);
	value1 = get_var(data, "NOT_A_VAR");
	if (*value1)
		return (1);
	free(value1);
	ft_printf("\n\n---------------------------\n\n");
	ft_env(data);
	tmp_arr = ft_make_test_strarr("LOGNAME");
	ft_unset(data, tmp_arr);
	free(tmp_arr);
	value1 = get_var(data, "LOGNAME");
	if (*value1)
		return (1);
	free(value1);
	tmp_arr = ft_split("VAR1 VAR2 ERROR VAR4 VAR5", ' ');
	ft_unset(data, tmp_arr);
	ft_free_array((void **)tmp_arr, ft_arrlen(tmp_arr));
	value1 = get_var(data, "VAR1");
	value2 = get_var(data, "VAR2");
	value3 = get_var(data, "ERROR");
	value4 = get_var(data, "VAR3");
	value5 = get_var(data, "VAR4");
	value6 = get_var(data, "VAR5");
	if (*value1 || *value2 || *value3 || !*value4 || *value5 || *value6)
		return (1);
	free(value1);
	free(value2);
	free(value3);
	free(value4);
	free(value5);
	free(value6);
	ft_printf("\n\n---------------------------\n\n");
	ft_env(data);
	ft_lstclear(data->envp, free_var);
	free(data->envp);
	free(data);
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
