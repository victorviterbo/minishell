/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:08:58 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/07 13:16:33 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_data *data, char **args, int argc)
{
	int	i;

	if (!data->envp)
	{
		ft_error(data, "export: no environment variables set");
		return (EXIT_FAILURE);
	}
	if (argc == 1)
		return (export_no_args(data));
	i = 1;
	while (i < argc)
	{
		new_var(data, args[i]);
		if (data->exit_status)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	export_no_args(t_data *data)
{
	t_list	*copy;
	t_list	*current;
	t_var	*var;
	t_list	*best;

	copy = ft_lstmap_void(*data->envp, copy_var, free_var);
	if (!copy)
		return (ft_error(data, "export: could not display environment"),
			EXIT_FAILURE);
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
