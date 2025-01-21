/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:08:58 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/21 13:50:29 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(char *args[], char *envp[]);
int	change_envp(char *str, char *envp[], bool append);

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
	size_t	namelen;
	int		i;

	name = ft_substr(str, 0, ft_strchr(str, '=') - append - str);
	if (!name)
		ft_custom_error_exit("Minishell: export: Error in allocating memory");
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(name, envp[i], ft_strlen(name)) == 0
			&& ft_strchr("+=", envp[i][ft_strlen(name) + 1]))
			rewrite_var(str, envp, i, append);
		i++;
	}
	if (!envp[i])
		ft_array_append(envp[i], str, false);
	return (free(name), 0);
}

int	rewrite_var(char *str, char *envp[], int i, bool append)
{
	if (append)
		envp[i] = ft_strjoin_ip(envp[i], ft_strchr(str, '=') + 1, FREE_S1S2);
	else
	{
		free(envp[i]);
		envp[i] = ft_strdup(str);
	}
	if (!envp[i])
		ft_custom_error_exit("Minishell: export: Error in allocating memory");
	return (0);
}
