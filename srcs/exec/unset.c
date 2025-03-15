/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:21:35 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/15 16:15:59 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_data *data, char **varnames);
void	pop_var(t_data *data, char *varname);
void	free_var(void *data);

void	ft_unset(t_data *data, char **varnames)
{
	int	i;

	i = 0;
	while (varnames[i])
	{
		pop_var(data, varnames[i]);
		if (data->exit_status)
			return ;
		i++;
	}
	return ;
}

void	pop_var(t_data *data, char *varname)
{
	t_list	*current;
	t_list	*last;
	t_var	*var;

	if (!data || !data->envp || !varname)
		return (ft_error(data, "unset: no env found or not a valid argument"));
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
	data->exit_status = (current == NULL);
	return ;
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
