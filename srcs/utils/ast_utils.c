/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:14:18 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/07 13:31:12 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_tree_node(t_data *data, char type)
{
	t_node	*new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (ft_error(data, "malloc: memory allocation failed"), NULL);
	new_node->type = type;
	return (new_node);
}

void	free_tree(t_node *node)
{
	if (!node)
		return ;
	if (node->left)
	{
		free_tree(node->left);
		node->left = NULL;
	}
	if (node->right)
	{
		free_tree(node->right);
		node->right = NULL;
	}
	free_tokens(node->redi);
	node->redi = NULL;
	free_tokens(node->args);
	node->args = NULL;
	free(node);
}

t_pfunc	is_builtin(char *str, t_builtin *builtin)
{
	unsigned int	i;
	unsigned int	name_len;

	if (!str)
		return (NULL);
	i = 0;
	while (builtin[i].name)
	{
		name_len = ft_strlen(builtin[i].name);
		if (ft_strncmp(str, builtin[i].name, name_len) == 0 && \
			str[name_len] == '\0')
			return (builtin[i].func);
		i++;
	}
	return (NULL);
}

unsigned int	token_list_size(t_token *list)
{
	unsigned int	size;

	size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	return (size);
}

char	**token_list_to_args(t_data *data, t_token *token_list)
{
	unsigned int	i;
	char			**args;

	args = ft_calloc(token_list_size(token_list) + 1, sizeof(char *));
	if (!args)
		return (ft_error(data, "malloc: memory allocation failed"), NULL);
	i = 0;
	while (token_list)
	{
		args[i] = ft_strdup(token_list->str);
		if (!args[i])
			return (ft_error(data, "malloc: memory allocation failed"), \
				ft_free_array((void **)args, ft_arrlen(args)), NULL);
		token_list = token_list->next;
		i++;
	}
	return (args);
}
