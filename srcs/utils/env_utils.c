/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:50:47 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/31 02:27:53 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_data *data, char **envp);

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
