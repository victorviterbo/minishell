/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:14:18 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/09 12:39:13 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_trav(t_data *data, t_tree *tree);
void	tree_error(t_token *token, t_tree *tree);
void	free_leaf(t_leaf *leaf);

void	ast_trav(t_data *data, t_tree *tree)
{
	if (tree->left)
		ft_ast_trav(data, tree->left);
	if (tree->right)
		ft_ast_trav(data, tree->right);
	if (!tree->left && !tree->right)
		make_leaf(data, tree);
	return ;
}

void	tree_error(t_token *token, t_tree *tree)
{
	if (token)
		free_tokens(token);
	if (tree->left)
		tree_error(NULL, tree->left);
	if (tree->right)
		tree_error(NULL, tree->right);
	if (!tree->left && !tree->right)
		free_leaf(tree->content);
	free(tree->content);
	free(tree);
	return ;
}

void	free_leaf(t_leaf *leaf)
{
	if (leaf->args)
		ft_free_array((void **)leaf->args, ft_arrlen(leaf->args));
	if (leaf->cmd)
		free(leaf->cmd);
	return ;
}
