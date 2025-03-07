/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:47:44 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/20 15:59:17 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_tree(char *str, t_tree *tree);
char	*is_cmd_separator(char c1, char c2, bool openpar);
void	explore_subtree(t_tree *tree, char *str, size_t i, size_t seplen);

void	build_tree(char *str, t_tree *tree)
{
	int		*isescaped;
	char	*sep;
	size_t	i;

	str = ft_strtrim(str, "\011\012\013\014\015\040");
	isescaped = is_quote_escaped(str);
	i = -1;
	while (str[i + 1])
	{
		i++;
		if (isescaped[i])
			continue ;
		if (tree->parent)
			sep = is_cmd_separator(str[i], str[i + 1],
					ft_strcmp(tree->parent->content, "(") == 0);
		else
			sep = is_cmd_separator(str[i], str[i + 1], false);
		if (sep == NULL)
			continue ;
		else
		{
			tree->content = sep;
			explore_subtree(tree, str, i, ft_strlen(sep));
			return ;
		}
	}
	tree->content = ft_strdup(str);
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
