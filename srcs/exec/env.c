/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:36:38 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/31 00:44:04 by vbronov          ###   ########.fr       */
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
		printed = ft_printf("%s=%s\n", curr_var->name, curr_var->value);
		if (printed != (ft_strlen(curr_var->name)
				+ ft_strlen(curr_var->value) + 2))
			return (ft_error(data, "env: printing error"), EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
