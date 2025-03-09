/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:47:44 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/09 19:52:43 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_ast(t_data *data, t_token *token);
void	build_tree(t_token *token, t_tree *tree, bool openpar);
void	explore_tree(t_token *token, t_token *current, t_token *last,
			t_tree *tree);
t_leaf	*make_leaf(t_data *data, t_token *current);

void	make_ast(t_data *data, t_token *token)
{
	t_tree	*tree;

	tree = ft_calloc(1, sizeof(tree));
	if (!tree)
		return ;
	build_tree(token, tree, false);
	ast_trav(data, tree);
	return ;
}

void	build_tree(t_token *token, t_tree *tree, bool openpar)
{
	t_token	*current;
	t_token	*last;

	current = token;
	last = current;
	while (current && (current->type > 4 || openpar)
		&& current->type != CLOSEPAR)
	{
		last = current;
		current = current->next;
	}
	if (current)
		explore_tree(token, current, last, tree);
	else
		tree->content = token;
	return ;
}

void	explore_tree(t_token *token, t_token *current, t_token *last,
	t_tree *tree)
{
	tree->content = current->str;
	free_token(current);
	if (last != current)
	{
		tree->left = ft_calloc(1, sizeof(t_tree));
		if (!tree->left)
			return (tree_error_token(token, tree));
		last->next = NULL;
		build_tree(token, tree->left, false);
	}
	if (current->next)
	{
		tree->right = ft_calloc(1, sizeof(t_tree));
		if (!tree->right && last != current)
			return (tree_error_token(current->next, tree));
		else if (!tree->right)
			return ;
		build_tree(current->next, tree->right, current->type == OPENPAR);
	}
}

t_leaf	*make_leaf(t_data *data, t_token *current)
{
	t_leaf	*leaf;

	leaf = ft_calloc(1, sizeof(leaf));
	if (!leaf)
		return (NULL);
	leaf->args = ft_calloc(1, sizeof(char *));
	while (current)
	{	
		current->str = parse_str(data, current->str, true);
		if (current->type == WORD && leaf->cmd == NULL)
			leaf->cmd = current->str;
		else if (current->type == WORD)
			leaf->args = ft_array_append(leaf->args, current->str, false);
		else if (current->type > 5)
		{
			if (open_stream(leaf, current) < 0)
			{
				data->exit_status = errno;
				ft_fprintf(STDERR_FILENO, "open: %s\n", data->exit_status);
			}
			current = current->next;
		}
		current = current->next;
	}
	return (leaf);
}
