/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:14:18 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/09 19:48:47 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_trav(t_data *data, t_tree *tree);
void	tree_error_leaf(t_tree *tree);
void	tree_error_token(t_token *token, t_tree *tree);
void	free_leaf(t_leaf *leaf);

void	ast_trav(t_data *data, t_tree *tree)
{
	t_leaf	*leaf;

	if (tree->left)
		ast_trav(data, tree->left);
	if (tree->right)
		ast_trav(data, tree->right);
	if (!tree->left && !tree->right)
	{
		leaf = make_leaf(data, tree->content);
		if (!leaf)
			tree_error_leaf(tree);
	}
	return ;
}

void	tree_error_token(t_token *token, t_tree *tree)
{
	if (token)
		free_tokens(token);
	if (tree->left)
		tree_error_token(NULL, tree->left);
	if (tree->right)
		tree_error_token(NULL, tree->right);
	free_tokens(tree->content);
	free(tree);
	return ;
}

void	tree_error_leaf(t_tree *tree)
{
	if (tree->left)
		tree_error_leaf(tree->left);
	if (tree->right)
		tree_error_leaf(tree->right);
	if (!tree->left && !tree->right)
		free_leaf(tree->content);
	else
		free_tokens(tree->content);
	free(tree);
	return ;
}

void	free_leaf(t_leaf *leaf)
{
	if (leaf->args)
		ft_free_array((void **)leaf->args, ft_arrlen(leaf->args));
	if (leaf->cmd)
		free(leaf->cmd);
	if (leaf->limiter)
		free(leaf->limiter);
	return ;
}
