/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:08:58 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/13 13:36:27 by vviterbo         ###   ########.fr       */
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

static int	export_print_node(t_data *data, t_list *best)
{
	t_var	*var;
	size_t	printed;

	var = best->content;
	if (var->value)
	{
		printed = ft_printf("declare -x %s=\"%s\"\n", var->name, var->value);
		if (printed != ft_strlen(var->name) + ft_strlen(var->value) + 15)
			return (ft_error(data, "export: printing error"), EXIT_FAILURE);
	}
	else
	{
		printed = ft_printf("declare -x %s\n", var->name);
		if (printed != ft_strlen(var->name) + 12)
			return (ft_error(data, "export: printing error"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	export_no_args(t_data *data)
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
		if (export_print_node(data, best) == EXIT_FAILURE)
			return (ft_lstclear(&copy, free_var), EXIT_FAILURE);
		ft_lstpop(&copy, best, free_var);
	}
	return (EXIT_SUCCESS);
}
