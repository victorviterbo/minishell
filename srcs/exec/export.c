/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:08:58 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/21 13:43:00 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export(t_data *data, char *args[]);
int		export_no_args(t_data *data);

int	ft_export(t_data *data, char *args[])
{
	int		i;
	int		success;

	if (!data || !data->envp)
		ft_print_error("export: no env or not a valid argument");
	if (!args || !args[0])
		return (export_no_args(data));
	i = 0;
	success = 0;
	while (args[i])
	{
		success += new_var(data, args[i]);
		i++;
	}
	return (success);
}

int	export_no_args(t_data *data)
{
	t_list	*copy;
	t_list	*current;
	t_var	*var;
	t_list	*best;

	copy = ft_lstmap_void(*data->envp, copy_var, free_var);
	if (!copy)
		return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}
