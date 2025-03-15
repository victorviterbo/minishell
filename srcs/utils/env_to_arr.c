/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:49:19 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/15 16:30:39 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_arr(t_data *data);
char	*var_to_str(t_data *data, t_list *current);
void	update_env_arr(t_data *data);
void	change_shlvl(t_data *data, int change);
void	*copy_var(void	*var);

char	**env_to_arr(t_data *data)
{
	char	**envarr;
	t_list	*current;
	int		i;

	if (!data || !data->envp)
		return (ft_error(data, "env parsing: no environment found"), NULL);
	envarr = ft_calloc(ft_lstsize(*data->envp) + 1, sizeof(char *));
	if (!envarr)
		return (ft_error(data, "env parsing: memory allocation failed"), NULL);
	current = *data->envp;
	i = 0;
	while (current)
	{
		envarr[i] = var_to_str(data, current);
		if (data->exit_status)
			return (ft_free_array((void **)envarr, ft_arrlen(envarr)), NULL);
		current = current->next;
		i++;
	}
	envarr[i] = NULL;
	return (envarr);
}

char	*var_to_str(t_data *data, t_list *current)
{
	t_var	*curr_var;
	char	*varstr;

	if (!current)
		return (ft_error(data, "env parsing: not a valid argument"), NULL);
	curr_var = current->content;
	varstr = ft_strjoin(curr_var->name, "=");
	if (!varstr)
		return (ft_error(data, "env parsing: memory allocation failed"), NULL);
	varstr = ft_strjoin_ip(varstr, curr_var->value, FREE_S1);
	if (!varstr)
		return (ft_error(data, "env parsing: memory allocation failed"), NULL);
	return (varstr);
}

void	update_env_arr(t_data *data)
{
	if (data->env_arr)
		ft_free_array((void **)data->env_arr, ft_arrlen(data->env_arr));
	data->env_arr = env_to_arr(data);
	if (!data->env_arr)
		return (ft_error(data, "env array update: memory allocation failed"));
	return ;
}

void	change_shlvl(t_data *data, int change)
{
	int		current_shlvl;
	char	*shlvl;

	shlvl = get_var(data, "SHLVL");
	if (!ft_isint(shlvl))
		return (ft_error(data, "env parsing: shlvl is not an int"));
	current_shlvl = ft_atoi(shlvl);
	free(shlvl);
	shlvl = ft_itoa(current_shlvl + change);
	if (!shlvl)
		return (ft_error(data, "env parsing: memory allocation failed"));
	shlvl = ft_strjoin_ip("SHLVL=", shlvl, FREE_S2);
	new_var(data, shlvl);
	free(shlvl);
	return ;
}

void	*copy_var(void	*var)
{
	t_var	*copy;

	copy = ft_calloc(1, sizeof(t_var));
	if (!copy)
		return (NULL);
	copy->name = ft_strdup(((t_var *)var)->name);
	if (!copy->name)
		return (free(copy), NULL);
	copy->value = ft_strdup(((t_var *)var)->value);
	if (!copy->value)
		return (free(copy->name), free(copy->value), NULL);
	return (copy);
}
