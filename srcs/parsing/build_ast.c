/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:47:44 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:55 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_ast(t_data *data, t_token *token);
void	ast_trav(t_data *data, t_tree *tree);
void	build_tree(t_token *token, t_tree *tree, bool openpar);
void	explore_tree(t_token *token, t_token *current, t_token *last,
			t_tree *tree);
int		make_leaf(t_data *data, t_token *current, t_leaf *leaf);

void	make_ast(t_data *data, t_token *token)
{
	t_tree	*tree;

	tree = ft_calloc(1, sizeof(t_tree));
	if (!tree)
		return ;
	build_tree(token, tree, false);
	ast_trav(data, tree);
	data->tree = tree;
	return ;
}

void	ast_trav(t_data *data, t_tree *tree)
{
	t_leaf	*leaf;
	int		leaf_ok;

	if (tree->left)
		ast_trav(data, tree->left);
	if (tree->right)
		ast_trav(data, tree->right);
	if (!tree->left && !tree->right)
	{
		leaf = ft_calloc(1, sizeof(t_leaf));
		if (!leaf)
			return (tree_error_leaf(NULL, tree));
		leaf_ok = make_leaf(data, tree->content, leaf);
		if (leaf_ok != 0)
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

int	make_leaf(t_data *data, t_token *current, t_leaf *leaf)
{
	while (current)
	{
		current->str = parse_str(data, current->str, true);
		if (current->type == WORD)
		{
			leaf->args = ft_array_append(leaf->args, ft_strdup(current->str),
				false);
			if (!leaf->args)
				return (-1);
		}
		else if (current->type > 5 && current->next)
		{
			if (open_stream(leaf, current) < 0)
			{
				data->exit_status = errno;
				ft_fprintf(STDERR_FILENO, "open: %s\n", data->exit_status);
				return (data->exit_status);
			}
			current = current->next;
		}
		current = current->next;
	}
	return (0);
}
