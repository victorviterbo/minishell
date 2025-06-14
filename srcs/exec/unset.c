/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:21:35 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/26 15:37:33 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data *data, char **args, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		pop_var(data, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	pop_var(t_data *data, char *varname)
{
	t_list	*curr;
	t_list	*prev;
	t_var	*var;

	if (!data->envp || !varname || !ft_strcmp(varname, "_"))
		return ;
	curr = *(data->envp);
	prev = NULL;
	while (curr)
	{
		var = curr->content;
		if (ft_strcmp(var->name, varname) == 0)
		{
			if (!prev)
				*(data->envp) = curr->next;
			else
				prev->next = curr->next;
			ft_lstdelone(curr, free_var);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	free_var(void *data)
{
	t_var	*var;

	var = data;
	if (!var)
		return ;
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	free(var);
	return ;
}
