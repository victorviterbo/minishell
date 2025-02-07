/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:55:38 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/07 11:28:16 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_env(t_data *data, char **envp);
int		new_var(t_data *data, char *str);
int		add_var(t_data *data, t_list **env, char *str, size_t name_len);
int		change_var(t_data *data, t_list *current, char *first_equal,
			bool append);
char	*get_var(t_data *data, char *varname);

int	init_env(t_data *data, char **envp)
{
	int		i;
	int		success;

	i = 0;
	success = 0;
	if (!data)
		ft_print_error("env init: invalid call to function");
	if (!envp)
		ft_print_error("env init: invalid argument");
	data->envp = ft_calloc(1, sizeof(t_list *));
	if (!data->envp)
		ft_print_error("env init: memory allocation failed");
	while (envp[i])
	{
		success += new_var(data, envp[i]);
		i++;
	}
	update_env_arr(data);
	return (success);
}

int	new_var(t_data *data, char *str)
{
	char	*first_equal;
	bool	append;
	size_t	name_len;
	t_var	*curr_var;
	t_list	*current;

	first_equal = ft_strchr(str, '=');
	if (!first_equal || first_equal == str)
		return (EXIT_FAILURE);
	append = (*(first_equal - 1) == '+');
	name_len = first_equal - str - append;
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

int	add_var(t_data *data, t_list **env, char *str, size_t name_len)
{
	char	*first_equal;
	t_var	*new_var;

	first_equal = ft_strchr(str, '=');
	new_var = ft_calloc(1, sizeof(t_var));
	if (!new_var)
		ft_print_error("env: memory allocation failed");
	new_var->name = ft_substr(str, 0, name_len);
	if (!new_var->name)
		ft_print_error("env: memory allocation failed");
	new_var->value = ft_strdup(first_equal + 1);
	if (!new_var->value)
		ft_print_error("env: memory allocation failed");
	ft_lstadd_back(env, ft_lstnew_void(new_var));
	update_env_arr(data);
	return (EXIT_SUCCESS);
}

int	change_var(t_data *data, t_list *current, char *first_equal, bool append)
{
	t_var	*var;

	var = current->content;
	if (append)
		var->value = ft_strjoin_ip(var->value, first_equal + 1, FREE_S1);
	else
	{
		free(var->value);
		var->value = ft_strdup(first_equal + 1);
	}
	if (!var->value)
		ft_print_error("env: memory allocation failed");
	update_env_arr(data);
	return (EXIT_SUCCESS);
}

char	*get_var(t_data *data, char *varname)
{
	t_list	*current;
	t_var	*curr_var;

	current = *(data->envp);
	while (current)
	{
		curr_var = current->content;
		if (ft_strncmp(curr_var->name, varname, ft_strlen(varname) + 1) == 0)
			return (ft_strdup(curr_var->value));
		current = current->next;
	}
	return (ft_strdup(""));
}
