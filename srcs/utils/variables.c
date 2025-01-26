/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:55:38 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/26 20:14:05 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(char **envp, t_data *data);
int	new_var(t_list **env, char *str);
int	add_var(t_list **env, char *str, size_t name_len);
int	change_var(t_list *current, char *first_equal, bool append);

int	init_env(char **envp, t_data *data)
{
	int		i;
	int		success;

	i = 0;
	success = 0;
	data->envp = ft_calloc(1, sizeof(t_list *));
	if (!data->envp)
		return (1);
	while (envp[i])
	{
		success += new_var(data->envp, envp[i]);
		i++;
	}
	return (success);
}

int	new_var(t_list **env, char *str)
{
	char	*first_equal;
	bool	append;
	size_t	name_len;
	t_var	*var;
	t_list	*current;

	current = *env;
	first_equal = ft_strchr(str, '=');
	if (!first_equal || first_equal == str)
		return (1);
	append = (*(first_equal - 1) == '+');
	name_len = first_equal - str - append;
	while(current)
	{
		var = current->content;
		if (ft_strncmp(var->name, str, name_len) && 
			ft_strlen(var->name) == name_len)
			return (change_var(current, first_equal, append));
		current = current->next;
	}
	return (add_var(env, str, name_len));
}

int	add_var(t_list **env, char *str, size_t name_len)
{
	char	*first_equal;
	t_var	*new_var;

	first_equal = ft_strchr(str, '=');
	new_var = ft_calloc(1, sizeof(t_var));
	if (!new_var)
		return (1);
	new_var->name = ft_substr(str, 0, name_len);
	new_var->value = ft_strdup(first_equal + 1);
	ft_lstadd_back(env, ft_lstnew_void(new_var));
	return (0);
}

int	change_var(t_list *current, char *first_equal, bool append)
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
	return (0);
}
