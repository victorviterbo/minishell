/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd_leaks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/11 15:24:46 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*here;
	char	*pwd_var;
	char	*oldpwd_var;
	char	*pwd_var2;
	char	*oldpwd_var2;
	char	*curr_path;
	t_data	*data;
	pid_t	pid;

	(void)argc;
	(void)argv;
	here = ft_get_current_path();
	data = ft_calloc(1, sizeof(t_data));
	init_env(data, envp);
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
	ft_cd(data, here);
	pwd_var = get_var(data, "PWD");
	curr_path = ft_get_current_path();
	if (ft_strcmp(pwd_var, curr_path))
		return (EXIT_FAILURE);
	free(pwd_var);
	free(curr_path);
	pwd_var = get_var(data, "PWD");
	oldpwd_var = get_var(data, "OLDPWD");
	pid = fork();
	if (pid == 0)
	{
		if (ft_cd(data, "not_a_dir") == 0)
			return (EXIT_FAILURE);
	}
	pwd_var2 = get_var(data, "PWD");
	oldpwd_var2 = get_var(data, "OLDPWD");
	if (ft_strcmp(pwd_var, pwd_var2))
		return (EXIT_FAILURE);
	if (ft_strcmp(oldpwd_var, oldpwd_var2))
		return (EXIT_FAILURE);
	free(pwd_var);
	free(oldpwd_var);
	free(pwd_var2);
	free(oldpwd_var2);
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
		if (ft_cd(data, "test_pwd.c") == 0)
			return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		if (ft_cd(data, "lalala") == 0)
			return (EXIT_FAILURE);
	if (ft_cd(data, here) != 0)
		return (EXIT_FAILURE);
	here = ft_strjoin_ip(here, "/", FREE_S1);
	if (ft_cd(data, here) != 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		if (ft_cd(data, "~/Desktop/42/not_a_folder") == 0)
			return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		if (ft_cd(data, "~/Desktop/42/not_a_folder/") == 0)
			return (EXIT_FAILURE);
	free(here);
	ft_lstclear(data->envp, free_var);
	free(data->envp);
	ft_free_array((void **)data->env_arr, ft_arrlen(data->env_arr));
	free(data);
	return (EXIT_SUCCESS);
}
