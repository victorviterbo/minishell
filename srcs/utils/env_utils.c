/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:50:47 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/26 22:02:27 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_data *data, char **envp)
{
	int		i;

	i = 0;
	if (!envp)
		return (ft_error(data, "environment init: invalid argument"));
	data->envp = ft_calloc(1, sizeof(t_list *));
	if (!data->envp)
		return (ft_error(data, "environment init: memory allocation failed"));
	while (envp[i])
	{
		new_var(data, envp[i]);
		if (data->exit_status)
			return (free_env(data));
		i++;
	}
	change_shlvl(data, 1);
	if (data->exit_status)
		free_env(data);
}
