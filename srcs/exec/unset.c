/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:21:35 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/28 20:32:56 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unset(t_data *data, char **varnames);
int		pop_var(t_data *data, char *varname);
void	free_var(void *data);

int	ft_unset(t_data *data, char **varnames)
{
	int	i;
	int	success;

	i = 0;
	success = 0;
	while (varnames[i])
	{
		success += pop_var(data, varnames[i]);
		i++;
	}
	return (success);
}

int	pop_var(t_data *data, char *varname)
{
	t_list	*current;
	t_list	*last;
	t_var	*var;

	current = *(data->envp);
	last = NULL;
	while (current)
	{
		var = current->content;
		if (ft_strcmp(var->name, varname) == 0)
		{
			if (!last)
				data->envp = &current->next;
			else
				last->next = current->next;
			ft_lstdelone(current, free_var);
			break ;
		}
		last = current;
		current = current->next;
	}
	return ((current == NULL));
}

void	free_var(void *data)
{
	t_var	*var;

	var = data;
	free(var->name);
	free(var->value);
	free(var);
	return ;
}
