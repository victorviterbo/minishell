/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:47:44 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/16 15:35:42 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_tree(char *str, t_tree *tree);

void	build_tree(char *str, t_tree *tree)
{
	t_tree	*tree;
	int		*isescaped;
	size_t	i;

	isescaped = is_quote_escaped(str);
	i = -1;
	while (str[i + 1])
	{
		i++;
		if (str[i] == '(')
		{
			i = go_to_next(str, ")", i);
			continue ;
		}
		else if (!is_cmd_separator(str[i], str[i + 1]))
			continue ;
		else if (str[i] == '|' && str[i+ 1] == '|' && isescaped[i] == IS_NOT_QUOTED)
			tree->content = ft_strdup ("||");
		else if (str[i] == '&' && str[i + 1] == '&' && isescaped[i] == IS_NOT_QUOTED)
			tree->content = ft_strdup ("&&");
		else if (str[i] == '|' && isescaped[i] == IS_NOT_QUOTED)
			tree->content = ft_strdup ("|");
		build_tree(ft_substr(str, 0, i), tree->left);
		build_tree(ft_substr(str, i + 2,
				ft_strlen(i + 2 - (str[i + 1] != '|'))), tree->right);
		free(str);
		return ;
	}
}
