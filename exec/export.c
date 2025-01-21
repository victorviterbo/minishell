/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:08:58 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/21 18:05:22 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(char *args[], char *envp[]);
int	change_envp(char *str, char *envp[], bool append);
int	rewrite_var(char *str, char *envp[], int i, bool append);

int	ft_export(char *args[], char *envp[])
{
	int		i;
	char	*first_equal;
	int		success;

	i = 0;
	success = 0;
	while (args[i])
	{
		first_equal = ft_strchr(args[i], '=');
		ft_printf("first equal: %s\n", first_equal);
		if (first_equal == NULL)
			i++;
		else if (first_equal == args[i])
			ft_printf("Minishell: export: `%s': not a valid identifier",
				args[i]);
		else if (*(first_equal - 1) == '+')
			success += change_envp(args[i], envp, true);
		else
			success += change_envp(args[i], envp, false);
		i++;
	}
	return (success);
}

int	change_envp(char *str, char *envp[], bool append)
{
	char	*name;
	int		i;

	ft_printf("for str %s 1 ok in change\n", str);
	name = ft_substr(str, 0, ft_strchr(str, '=') - append - str);
	if (!name)
		ft_custom_error_exit("Minishell: export: Error in allocating memory");
	i = 0;
	ft_printf("for str %s 2 ok in change\n", str);
	while (envp[i])
	{
		if (ft_strncmp(name, envp[i], ft_strlen(name)) == 0
			&& ft_strchr("+=", envp[i][ft_strlen(name)]))
		{
			ft_printf("coucou for %s\n", str);
			rewrite_var(str, envp, i, append);
		}
		i++;
	}
	if (!envp[i])
	{
		ft_print_array(envp, true);
		envp = ft_array_append(envp, str, false);
		ft_print_array(envp, true);
		if (!envp)
			ft_custom_error_exit("Minishell: export:\
			 Error in allocating memory");
	}
	return (free(name), 0);
}

int	rewrite_var(char *str, char *envp[], int i, bool append)
{
	if (append)
		envp[i] = ft_strjoin_ip(envp[i], ft_strchr(str, '=') + 1, FREE_S1S2);
	else
	{

		ft_printf("for str %s 1 ok in rewrite\n", str);
		free(envp[i]);
		envp[i] = ft_strdup(str);
	}
	if (!envp[i])
		ft_custom_error_exit("Minishell: export: Error in allocating memory");
	return (0);
}
