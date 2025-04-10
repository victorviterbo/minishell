/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:36:38 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/10 17:50:59 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, char **args, int argc)
{
	t_list	*current;
	t_var	*curr_var;
	size_t	printed;

	if (argc > 1)
		return (ft_error(data, "env: too many arguments"), EXIT_FAILURE);
	(void)args;
	if (!data->envp)
		return (ft_error(data, "env: no environment variables set"),
			EXIT_FAILURE);
	current = *(data->envp);
	while (current)
	{
		curr_var = current->content;
		if (!curr_var->value)
			continue ;
		if (ft_printf("%s=%s\n", curr_var->name, curr_var->value)
			!= (ft_strlen(curr_var->name) + ft_strlen(curr_var->value) + 2))
			return (ft_error(data, "env: printing error"), EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
