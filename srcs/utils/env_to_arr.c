/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:49:19 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/29 01:11:43 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_arr(t_data *data);
char	*var_to_str(t_list *current);

char	**env_to_arr(t_data *data)
{
	char	**envarr;
	t_list	*current;
	int		i;

	if (!data || !data->envp)
		ft_custom_error_exit("Minishell: env parsing: no env found");
	envarr = ft_calloc(ft_lstsize(*data->envp) + 1, sizeof(char *));
	if (!envarr)
		ft_custom_error_exit("Minishell: env parsing: memory allocation \
failed");
	current = *data->envp;
	i = 0;
	while (current)
	{
		envarr[i] = var_to_str(current);
		current = current->next;
		i++;
	}
	envarr[i] = NULL;
	return (envarr);
}

char	*var_to_str(t_list *current)
{
	t_var	*curr_var;
	char	*varstr;

	if (!current)
		ft_custom_error_exit("Minishell: env parsing: not a valid argument");
	curr_var = current->content;
	varstr = ft_strjoin(curr_var->name, "=");
	if (!varstr)
		ft_custom_error_exit("Minishell: env parsing: memory allocation \
failed");
	varstr = ft_strjoin_ip(varstr, curr_var->value, FREE_S1);
	if (!varstr)
		ft_custom_error_exit("Minishell: env parsing: memory allocation \
failed");
	return (varstr);
}
