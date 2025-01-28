/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/28 10:58:17 by vviterbo         ###   ########.fr       */
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
	data = ft_calloc(1, sizeof(t_data));
	init_env(data, envp);
	ft_unset(data, ft_make_test_strarr("VAR1"));
	ft_unset(data, ft_make_test_strarr("VAR2"));
	ft_unset(data, ft_make_test_strarr("VAR3"));
	ft_unset(data, ft_make_test_strarr("VAR4"));
	ft_unset(data, ft_make_test_strarr("VAR5"));
	chdir(here);
	ft_export(data, ft_make_test_strarr("VAR1=test1"));
	value = get_var(data, "VAR1");
	if (ft_strcmp(value , "test1"))
		return (1);
	ft_env(data);
	free(value);
	ft_unset(data, ft_make_test_strarr("VAR1"));
	if (*get_var(data, "VAR1"))
		return (1);
	value = get_var(data, "VAR1");
	if (ft_strcmp(value , ""))
		return (1);
	ft_export(data, ft_make_test_strarr("VAR2=test=2"));
	value = get_var(data, "VAR2");
	if (ft_strcmp(value , "test=2"))
		return (1);
	free(value);
	ft_printf("\n\n---------------------------\n\n");
	ft_env(data);
	if (ft_export(data, ft_make_test_strarr("VAR1=")) == 0)
		return (1);
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
	ft_printf("\n\n---------------------------\n\n");
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
	if (*get_var(data, "NOT_A_VAR"))
		return (1);
	ft_printf("\n\n---------------------------\n\n");
	ft_env(data);
	ft_unset(data, ft_make_test_strarr("LOGNAME"));
	if (*get_var(data, "LOGNAME"))
		return (1);
	ft_unset(data, ft_split("VAR1 VAR2 ERROR VAR4 VAR5", ' '));
	if (*get_var(data, "VAR1") || *get_var(data, "VAR2") || *get_var(data, "ERROR") || !*get_var(data, "VAR3") || *get_var(data, "VAR4") || *get_var(data, "VAR5"))
		return (1);
	ft_printf("\n\n---------------------------\n\n");
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
