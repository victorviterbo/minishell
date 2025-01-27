/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:36:38 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/27 16:51:54 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data);

int	ft_env(t_data *data)
{
	t_list	*current;
	t_var	*curr_var;
	int		success;
	size_t	printed;

	current = *(data->envp);
	success = 0;
	while (current)
	{
		curr_var = current->content;
		printed = ft_printf("%s=%s\n", curr_var->name, curr_var->value);
		if (printed != (ft_strlen(curr_var->name)
				+ ft_strlen(curr_var->value) + 2))
			success += 1;
		current = current->next;
	}
	return (success);
}
