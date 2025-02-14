/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pwd_leaks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/12 12:54:11 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*here;
	char	*pwd_var;
	char	*oldpwd_var;
	char	*curr_path;
	t_data	*data;
	pid_t	pid;

	(void)argc;
	(void)argv;
	here = ft_get_current_path();
	data = ft_calloc(1, sizeof(t_data));
	init_env(data, envp);
	if (ft_pwd() != 0)
		return (EXIT_FAILURE);
	pwd_var = get_var(data, "PWD");
	curr_path = ft_get_current_path();
	if (ft_strcmp(pwd_var, curr_path))
		return (EXIT_FAILURE);
	if (ft_cd(data, "testdir") != 0)
		return (EXIT_FAILURE);
	oldpwd_var = get_var(data, "OLDPWD");
	if (ft_strcmp(pwd_var, oldpwd_var))
		return (EXIT_FAILURE);
	free(oldpwd_var);
	free(pwd_var);
	free(curr_path);
	pwd_var = get_var(data, "PWD");
	curr_path = ft_get_current_path();
	if (ft_strcmp(pwd_var, curr_path))
		return (EXIT_FAILURE);
	free(pwd_var);
	free(curr_path);
	if (ft_pwd() != 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		if (ft_cd(data, "not_a_dir") == 0)
			return (EXIT_FAILURE);
	}
	if (ft_pwd() != 0)
		return (EXIT_FAILURE);
	ft_cd(data, here);
	free(here);
	ft_lstclear(data->envp, free_var);
	free(data->envp);
	ft_free_array((void **)data->env_arr, ft_arrlen(data->env_arr));
	free(data);
	return (EXIT_SUCCESS);
}
