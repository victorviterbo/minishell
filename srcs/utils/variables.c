/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:55:38 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/25 16:54:37 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_var(t_data *data, char *str)
{
	char	*first_equal;
	bool	append;
	size_t	name_len;
	t_var	*curr_var;
	t_list	*current;

	first_equal = ft_strchr(str, '=');
	append = false;
	if (first_equal)
		append = (*(first_equal - 1) == '+');
	if (first_equal)
		name_len = first_equal - str - append;
	else
		name_len = ft_strlen(str);
	current = *(data->envp);
	while (current)
	{
		curr_var = current->content;
		if (ft_strncmp(curr_var->name, str, name_len) == 0
			&& ft_strlen(curr_var->name) == name_len)
			return (change_var(data, current, first_equal, append));
		current = current->next;
	}
	return (add_var(data, data->envp, str, name_len));
}

void	add_var(t_data *data, t_list **env, char *str, size_t name_len)
{
	char	*first_equal;
	t_var	*new_var;
	t_list	*new_node;

	first_equal = ft_strchr(str, '=');
	new_var = ft_calloc(1, sizeof(t_var));
	if (!new_var)
		return (ft_error(data, "env: memory allocation failed"));
	new_var->name = check_varname(data, str, name_len);
	if (!new_var->name)
		return (free_var(new_var));
	if (first_equal)
	{
		new_var->value = ft_strdup(first_equal + 1);
		if (!new_var->value)
			return (free_var(new_var),
				ft_error(data, "env: memory allocation failed"));
	}
	new_node = ft_lstnew_void(new_var);
	if (!new_node)
		return (free_var(new_var),
			ft_error(data, "env: creation of new variable failed"));
	ft_lstadd_back(env, new_node);
	return ;
}

void	change_var(t_data *data, t_list *current,
	char *first_equal, bool append)
{
	t_var	*var;

	if (first_equal == NULL)
		return ;
	var = current->content;
	if (!var->value)
		var->value = ft_strdup(first_equal + 1);
	else if (append)
		var->value = ft_strjoin_ip(var->value, first_equal + 1, FREE_S1);
	else
	{
		free(var->value);
		var->value = ft_strdup(first_equal + 1);
	}
	if (!var->value)
		return (ft_error(data, "env: memory allocation failed"));
}

char	*get_var(t_data *data, char *varname)
{
	t_list	*current;
	char	*var_str;

	if (*varname == '?')
		return (get_last_exit_status(data, varname));
	current = *(data->envp);
	while (current)
	{
		if (ft_strncmp(((t_var *)current->content)->name, varname,
				ft_strlen(varname) + 1) == 0)
		{
			var_str = ft_strdup(((t_var *)current->content)->value);
			if (!var_str)
				return (ft_error(data,
						"variable access: memory allocation failed"), NULL);
			return (var_str);
		}
		current = current->next;
	}
	return (NULL);
}

char	*get_last_exit_status(t_data *data, char *varname)
{
	char	*var_str;

	if (ft_strcmp(varname, "?"))
	{
		ft_printf("%s: ${%s}: bad substitution\n", SHELL_NAME, varname);
		data->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	var_str = ft_itoa(data->last_exit_status);
	if (!var_str)
	{
		ft_error(data, "env: could not retrieve last exit status");
		return (NULL);
	}
	else
		return (var_str);
}
