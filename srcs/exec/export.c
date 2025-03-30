/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:08:58 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/15 17:18:12 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_data *data, char *args[]);
void	export_no_args(t_data *data);

void	ft_export(t_data *data, char *args[])
{
	int		i;

	if (!data || !data->envp)
		return (ft_error(data, "export: no environment found"));
	if (!args || !args[0])
		return (export_no_args(data));
	i = 0;
	while (args[i])
	{
		new_var(data, args[i]);
		if (data->exit_status)
			return ;
		i++;
	}
	return ;
}

void	export_no_args(t_data *data)
{
	t_list	*copy;
	t_list	*current;
	t_var	*var;
	t_list	*best;

	copy = ft_lstmap_void(*data->envp, copy_var, free_var);
	if (!copy)
		return (ft_error(data, "export: could not display environment"));
	while (copy)
	{
		current = copy;
		best = current;
		while (current)
		{
			var = current->content;
			if (ft_strcmp(var->name, ((t_var *)(best->content))->name) < 0)
				best = current;
			current = current->next;
		}
		ft_printf("declare -x %s=\"%s\"\n", ((t_var *)(best->content))->name,
			((t_var *)(best->content))->value);
		ft_lstpop(&copy, best, free_var);
	}
	return ;
}
