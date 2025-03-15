/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:36:38 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/15 17:07:57 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data);

void	ft_env(t_data *data)
{
	t_list	*current;
	t_var	*curr_var;
	size_t	printed;

	if (!data)
		return (ft_error(data, "env: invalid function call"));
	if (!data->envp)
		return (ft_error(data, "env: no environment found"));
	current = *(data->envp);
	while (current)
	{
		curr_var = current->content;
		printed = ft_printf("%s=%s\n", curr_var->name, curr_var->value);
		if (printed != (ft_strlen(curr_var->name)
				+ ft_strlen(curr_var->value) + 2))
			return (ft_error(data, "env: could not display environment"));
		current = current->next;
	}
	return ;
}
