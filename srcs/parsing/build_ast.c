/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:47:44 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/01 00:22:21 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_ast(t_data *data, t_token *token);
void	ast_trav(t_data *data, t_tree *tree);
void	build_tree(t_token *token, t_tree *tree, bool openpar);
void	explore_tree(t_token *token, t_token *current, t_token *last,
			t_tree *tree);
void	make_leaf(t_data *data, t_token *current, t_leaf *leaf);

void	make_ast(t_data *data, t_token *token)
{
	t_tree	*tree;

	tree = ft_calloc(1, sizeof(t_tree));
	if (!tree)
		return (ft_error(data, "parsing: memory allocation failed"));
	build_tree(token, tree, false);
	ast_trav(data, tree);
	data->tree = tree;
	return ;
}

void	ast_trav(t_data *data, t_tree *tree)
{
	t_leaf	*leaf;

	if (tree->left)
		ast_trav(data, tree->left);
	if (tree->right)
		ast_trav(data, tree->right);
	if (!tree->left && !tree->right)
	{
		leaf = ft_calloc(1, sizeof(t_leaf));
		if (!leaf)
			return (tree_error_leaf(NULL, tree), ft_error(data, "parsing: \
memory allocation failed"));
		make_leaf(data, tree->content, leaf);
		if (data->exit_status)
			return (tree_error_leaf(leaf, tree));
		free_tokens(tree->content);
		tree->content = leaf;
	}
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
	tree->content = current;
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
	current->next = NULL;
}

void	make_leaf(t_data *data, t_token *current, t_leaf *leaf)
{
	while (current)
	{
		// TODO: fix parse_str
		// current->str = parse_str(data, current->str, true);
		if (current->type == WORD)
		{
			leaf->args = ft_array_append(leaf->args, ft_strdup(current->str),
					false);
			if (!leaf->args)
				return (ft_error(data, "parsing: memory allocation failed"));
		}
		else if (current->type > 5 && current->next)
		{
			if (open_stream(data, leaf, current) < 0)
			{
				if (data->exit_status)
					return ;
				return (ft_error(data, "open: file opening failed"));
			}
			current = current->next;
		}
		current = current->next;
	}
	return ;
}
