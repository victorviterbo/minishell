/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:08:58 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/25 19:07:34 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char *args[], t_env *env);
int	change_envp(char *str, t_env *env, bool append);
int	rewrite_var(char *str, t_env *env, int i, bool append);

int	ft_export(char *args[], t_env *env)
{
	int		i;
	char	*first_equal;
	int		success;

	i = 0;
	success = 0;
	while (args[i])
	{
		first_equal = ft_strchr(args[i], '=');
		if (first_equal == NULL)
			i++;
		else if (first_equal == args[i])
			ft_printf("Minishell: export: `%s': not a valid identifier",
				args[i]);
		else if (*(first_equal - 1) == '+')
			success += change_envp(args[i], env, true);
		else
			success += change_envp(args[i], env, false);
		i++;
	}
	return (success);
}

int	change_envp(char *str, t_env *env, bool append)
{
	char	*name;
	int		i;

	name = ft_substr(str, 0, ft_strchr(str, '=') - append - str);
	if (!name)
		ft_custom_error_exit("Minishell: export: Error in allocating memory");
	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(name, env->envp[i], ft_strlen(name)) == 0
			&& ft_strlen(env->envp[i]) > ft_strlen(name)
			&& ft_strchr("+=", env->envp[i][ft_strlen(name)]))
			rewrite_var(str, env, i, append);
		i++;
	}
	if (!env->envp[i])
	{
		env->envp = ft_array_append(env->envp, ft_strdup(str), false);
		if (!env->envp)
			ft_custom_error_exit("Minishell: export:\
			 Error in allocating memory");
	}
	return (free(name), 0);
}

int	rewrite_var(char *str, t_env *env, int i, bool append)
{
	ft_printf("rewriting var : %s with : %s\n", env->envp[i], str);
	if (append)
		env->envp[i] = ft_strjoin_ip(env->envp[i], ft_strchr(str, '=') + 1,
				FREE_S1);
	else
	{
		ft_printf("1_1\n");
		free(env->envp[i]);
		ft_printf("1_2\n");
		env->envp[i] = ft_strdup(str);
	}
	if (!env->envp[i])
		ft_custom_error_exit("Minishell: export: Error in allocating memory");
	return (0);
}
