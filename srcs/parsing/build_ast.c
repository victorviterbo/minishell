/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:47:44 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/09 13:17:08 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_ast(t_data *data, t_token *token);
void	build_tree(t_token *token, t_tree *tree, bool openpar);
void	explore_tree(t_token *token, t_token *current, t_token *last,
			t_tree *tree);
void	make_leaf(t_data *data, t_tree *tree);

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
			return (tree_error(token, tree));
		last->next = NULL;
		build_tree(token, tree->left, false);
	}
	if (current->next)
	{
		tree->right = ft_calloc(1, sizeof(t_tree));
		if (!tree->right && last != current)
			return (tree_error(current->next, tree));
		else if (!tree->right)
			return ;
		build_tree(current->next, tree->right, current->type == OPENPAR);
	}
}

void	make_leaf(t_data *data, t_tree *tree)
{
	t_leaf	*leaf;
	t_token	*current;

	if (tree->left || tree->right)
		return ;
	leaf = ft_calloc(1, sizeof(t_leaf));
	current = ((t_token *)tree->content);
	leaf->args = ft_calloc(1, sizeof(char *));
	while (current)
	{	
		current->str = parse_str(data, current->str, true);
		if (current->type == WORD && leaf->cmd == NULL)
			leaf->cmd = current->str;
		else if (current->type == WORD)
			leaf->args = ft_array_append(leaf->args, current->str, false);
		else if (current->type == STDIN || current->type == STDIN_HEREDOC)
			leaf->fdin = open_stream(current);
		else if (current->type == STDOUT || current->type == STDOUT_APPEND)
			leaf->fdout = open_stream(current);
		if (current->type > 5)
			current = current->next;
		current = current->next;
	}
	tree->content = leaf;
	return ;
}
