/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/29 01:16:15 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_make_test_strarr(char *str);
static int	check_env_to_arr(t_data *data_orig);

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
		return (EXIT_FAILURE);
	free(value1);
	tmp_arr = ft_make_test_strarr("VAR1");
	ft_unset(data, tmp_arr);
	free(tmp_arr);
	value1 = get_var(data, "VAR1");
	if (*value1)
		return (EXIT_FAILURE);
	free(value1);
	value1 = get_var(data, "VAR1");
	if (ft_strcmp(value1 , ""))
		return (EXIT_FAILURE);
	free(value1);
	tmp_arr = ft_make_test_strarr("VAR2=test=2");
	ft_export(data, tmp_arr);
	free(tmp_arr);
	value1 = get_var(data, "VAR2");
	if (ft_strcmp(value1 , "test=2"))
		return (EXIT_FAILURE);
	free(value1);
	if (ft_env(data) != 0)
		return (EXIT_FAILURE);
	tmp_arr = ft_make_test_strarr("VAR1=");
	if (ft_export(data, tmp_arr) != 0)
		return (EXIT_FAILURE);
	free(tmp_arr);
	value1 = get_var(data, "VAR1");
	if (ft_strcmp(value1 , ""))
		return (EXIT_FAILURE);
	free(value1);
	pid = fork();
	if (pid == 0)
	{
		tmp_arr2 = ft_make_test_strarr("=test1");
		ft_export(data, tmp_arr2);
		free(tmp_arr2);
		return (EXIT_FAILURE);
	}
	tmp_arr = ft_make_test_strarr("VAR2+=lala");
	ft_export(data, tmp_arr);
	free(tmp_arr);
	value1 = get_var(data, "VAR2");
	if (ft_strcmp(value1 , "test=2lala"))
		return (EXIT_FAILURE);
	free(value1);
	tmp_arr = ft_make_test_strarr("VAR1=lili");
	ft_export(data, tmp_arr);
	free(tmp_arr);
	value1 = get_var(data, "VAR1");
	if (ft_strcmp(value1 , "lili"))
		return (EXIT_FAILURE);
	free(value1);
	tmp_arr = ft_split("VAR3=3 VAR4=4 VAR5=5", ' ');
	ft_export(data, tmp_arr);
	ft_free_array((void **)tmp_arr, ft_arrlen(tmp_arr));
	value1 = get_var(data, "VAR3");
	if (ft_strcmp(value1 , "3"))
		return (EXIT_FAILURE);
	free(value1);
	value1 = get_var(data, "VAR4");
	if (ft_strcmp(value1 , "4"))
		return (EXIT_FAILURE);
	free(value1);
	value1 = get_var(data, "VAR5");
	if (ft_strcmp(value1 , "5"))
		return (EXIT_FAILURE);
	free(value1);
	tmp_arr = ft_split("VAR3=6 =4 VAR5=7", ' ');
	ft_export(data, tmp_arr);
	ft_free_array((void **)tmp_arr, ft_arrlen(tmp_arr));
	if (ft_env(data) != 0)
		return (EXIT_FAILURE);
	value1 = get_var(data, "VAR3");
	if (ft_strcmp(value1 , "6"))
		return (EXIT_FAILURE);
	free(value1);
	value1 = get_var(data, "VAR5");
	if (ft_strcmp(value1 , "7"))
		return (EXIT_FAILURE);
	free(value1);
	tmp_arr = ft_make_test_strarr("NOT_A_VAR");
	ft_unset(data, tmp_arr);
	free(tmp_arr);
	value1 = get_var(data, "NOT_A_VAR");
	if (*value1)
		return (EXIT_FAILURE);
	free(value1);
	tmp_arr = ft_make_test_strarr("LOGNAME");
	ft_unset(data, tmp_arr);
	free(tmp_arr);
	value1 = get_var(data, "LOGNAME");
	if (*value1)
		return (EXIT_FAILURE);
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
		return (EXIT_FAILURE);
	free(value1);
	free(value2);
	free(value3);
	free(value4);
	free(value5);
	free(value6);
	if (ft_env(data) != 0)
		return (EXIT_FAILURE);
	if (check_env_to_arr(data) != 0)
		return (EXIT_FAILURE);
	ft_lstclear(data->envp, free_var);
	free(data->envp);
	free(data);
	return (EXIT_SUCCESS);
}

static char	**ft_make_test_strarr(char *str)
{
	char	**test_arr;

	test_arr = ft_calloc(2, sizeof(char *));
	test_arr[0] = str;
	test_arr[1] = NULL;
	return (test_arr);
}

static int	check_env_to_arr(t_data *data_orig)
{
	char	**env_arr;
	t_data	*data_copy;
	t_list	*curr_orig;
	t_list	*curr_copy;
	t_var	*var_orig;
	t_var	*var_copy;
	int		success;

	env_arr = env_to_arr(data_orig);
	data_copy = ft_calloc(1, sizeof(t_data));
	if (init_env(data_copy, env_arr) != 0)
		return (EXIT_FAILURE);
	curr_orig = *data_orig->envp;
	curr_copy = *data_copy->envp;
	while (curr_orig && curr_copy)
	{
		var_orig = curr_orig->content;
		var_copy = curr_copy->content;
		if (ft_strcmp(var_orig->name, var_copy->name))
			break ;
		if (ft_strcmp(var_orig->value, var_copy->value))
			break ;
		curr_orig = curr_orig->next;
		curr_copy = curr_copy->next;
	}
	if (curr_orig || curr_copy)
		success = EXIT_FAILURE;
	else
		success = EXIT_SUCCESS;
	ft_free_array((void **)env_arr, ft_arrlen(env_arr));
	ft_lstclear(data_copy->envp, free_var);
	free(data_copy->envp);
	free(data_copy);
	return (success);
}
