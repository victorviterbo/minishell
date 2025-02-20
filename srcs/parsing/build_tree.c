/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:47:44 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/16 18:20:00 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_tree(char *str, t_tree *tree);
bool	is_cmd_separator(char c1, char c2);
void	create_node(t_tree *tree, char *str, size_t i);
char	*parse_parenthesis(char *str, bool inplace);

void	build_tree(char *str, t_tree *tree)
{
	int		*isescaped;
	size_t	i;

	str = remove_parenthesis(str);
	isescaped = is_quote_escaped(str);
	i = -1;
	while (str[i + 1])
	{
		i++;
		if (!is_cmd_separator(str[i], str[i + 1]) | isescaped[i])
			continue ;
		else
			create_node(tree, str, i);
		free(str);
		return ;
	}
}

bool	is_cmd_separator(char c1, char c2)
{
	if (c1 == '|')
		return (true);
	else if (c1 == '&' && c2 == '&')
		return (true);
	else if (c1 == '(')
		return (true);
	return (false);
}

void	create_node(t_tree *tree, char *str, size_t i)
{
	size_t	j;

	if (str[i] == '(')
	{
		tree->content = ft_strdup("()");
		j = go_to_next(str, ")", i);
		build_tree(ft_substr(str, 0, j), tree->left);
		build_tree(ft_substr(str, j, ft_strlen(str + j)), tree->right);
		return ;
	}
	else if (str[i] == '|' && str[i+ 1] == '|')
		tree->content = ft_strdup ("||");
	else if (str[i] == '&' && str[i + 1] == '&')
		tree->content = ft_strdup ("&&");
	else if (str[i] == '|')
		tree->content = ft_strdup ("|");
	build_tree(ft_substr(str, 0, i), tree->left);
	build_tree(ft_substr(str, i + 2,
			ft_strlen(str + i + 2 - (str[i + 1] != '|'))), tree->right);
	return ;
}
