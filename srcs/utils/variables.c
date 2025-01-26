/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:55:38 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/26 14:55:20 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**init_env(char **envp);
int		new_var(t_list **env, char *str);
int		add_var(t_list **env, char *str);
int		change_var(t_list **env, char *str);

t_list	**init_env(char **envp)
{
	t_list	**env;
	int		i;
	int		success;

	i = 0;
	success = 0;
	env = ft_calloc(1, sizeof(t_list *));
	while (envp[i])
	{
		success += new_var(env, envp[i]);
		i++;
	}
	return (success);
}

int	new_var(t_list **env, char *str)
{
	char	*first_equal;
	bool	append;
	size_t	name_len;

	first_equal = ft_strchr(str, '=');
	if (!first_equal || first_equal == str)
		return (1);
	append = (*(first_equal - 1) == '+');
	name_len = first_equal - str - append;
	if (ft_lst_isin_void)
}

int	add_var(t_list **env, char *str)
{
	char	*first_equal;
	bool	append;
	size_t	name_len;
	t_var	*new_var;
	t_list	*current;

	current = *env;
	first_equal = ft_strchr(str, '=');
	if (!first_equal || first_equal == str)
		return (1);
	append = (*(first_equal - 1) == '+');
	name_len = first_equal - str - append;
	while(current)
	{
		if (ft_strncmp(current->content->name, str, name_len))
		{
			if (append)
				current->content->value = ft_strjoin_ip(current->content->value,
				first_equal + 1, FREE_S1);
			else
			{
				free(current->content->value);
				current->content->value = ft_strdup(first_equal + 1);
			}
			return (0);
		}
		current = current->next;
	}
	new_var = ft_calloc(1, sizeof(t_var));
	new_var->name = ft
}

			new_var = ft_calloc(1, sizeof(t_var));
			new_var->name = ft_substr(envp[i], 0, first_equal - envp[i]);
			new_var->value = ft_substr(first_equal + 1, 0,
				ft_strlen(first_equal));
			ft_lstadd_back(env, ft_lstnew_void(new_var));