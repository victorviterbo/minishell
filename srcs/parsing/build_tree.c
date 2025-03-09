/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:47:44 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/09 10:19:37 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_cmd_separator(char c1, char c2, bool openpar);
void	explore_subtree(t_tree *tree, char *str, size_t i, size_t seplen);

void	build_tree(t_token **token, t_tree *tree, bool openpar);

void	build_tree(t_token **token, t_tree *tree, bool openpar)
{
	t_token	*current;
	t_token	*last;

	current = *token;
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
		make_leaf(token, tree);
	return ;
}

void	explore_tree(t_token **token, t_token *current, t_token *last,
	t_tree *tree)
{
	((t_leaf *)tree->content)->operator = current->type;
	free_token(current);
	if (last != current)
	{
		tree->left = ft_calloc(1, sizeof(t_tree));
		if (!tree->left)
			return ;
		last->next = NULL;
		build_tree(token, tree->left, false);
	}
	if (current->next)
	{
		tree->right = ft_calloc(1, sizeof(t_tree));
		if (!tree->right && last != current)
			return (free(tree->left));
		else if (!tree->right)
			return ;
		build_tree(&current->next, tree->right, current->type == OPENPAR);
	}
}

void	parse_parenthesis(t_token **token, t_token *current, t_token *last,
	t_tree *tree)
{
	t_token	*end_par;

	end_par = current;
	while (end_par && end_par->type != CLOSEPAR)
		end_par = end_par->next;
	if (!end_par)
		return (ft_tree_clear(tree, free_node));
	if (last != current)
	{
		tree->left = ft_calloc(1, sizeof(t_tree));
		if (!tree->left)
			return ;
		last->next = NULL;
		build_tree(token, tree->left, false);
	}
	if (current->next)
	{
		tree->right = ft_calloc(1, sizeof(t_tree));
		if (!tree->right && last != current)
			return (free(tree->left));
		else if (!tree->right)
			return ;
		build_tree(&current->next, tree->right, false);
	}
}

void	make_leaf(t_token **token, t_tree *tree)
{
	return ;
}

char	*is_cmd_separator(char c1, char c2, bool openpar)
{
	if (c1 == '|' && c2 != '|' && !openpar)
		return (ft_strdup("|"));
	if (c1 == '|' && c2 == '|' && !openpar)
		return (ft_strdup("||"));
	else if (c1 == '&' && c2 == '&' && !openpar)
		return (ft_strdup("&&"));
	else if (c1 == '(' && !openpar)
		return (ft_strdup("("));
	else if (c1 == ')')
		return (ft_strdup(")"));
	return (NULL);
}

void	explore_subtree(t_tree *tree, char *str, size_t i, size_t seplen)
{
	if (i)
	{
		tree->left = ft_calloc(1, sizeof(t_tree));
		if (!tree->left)
			return ;
		tree->left->parent = tree;
		build_tree(ft_substr(str, 0, i), tree->left);
	}
	if (i != ft_strlen(str))
	{
		tree->right = ft_calloc(1, sizeof(t_tree));
		if (!tree->right)
			return (free(tree->right));
		tree->right->parent = tree;
		build_tree(ft_substr(str, i + seplen,
				ft_strlen(str + seplen)), tree->right);
	}
	return ;
}
