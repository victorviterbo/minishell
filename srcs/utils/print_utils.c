/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 03:57:29 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/27 01:38:58 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_token_list(t_token *token)
{
	if (!token)
	{
		ft_printf("empty token list\n");
		return ;
	}
	while (token)
	{
		ft_printf("\"%s\" TYPE: %i HEREDOC_FD: %i ",
			token->str, token->type, token->heredoc_fd);
		token = token->next;
	}
	ft_printf("\n");
}

static void	display_leaf(t_node *node, int depth, int *siblings)
{
	int	i;

	ft_printf("CMD\n");
	i = 0;
	while (i < depth)
	{
		if (siblings[i])
			ft_printf("│   ");
		else
			ft_printf("    ");
		i++;
	}
	ft_printf("  args: ");
	display_token_list(node->args);
	i = 0;
	while (i < depth)
	{
		if (siblings[i])
			ft_printf("│   ");
		else
			ft_printf("    ");
		i++;
	}
	ft_printf("  redi: ");
	display_token_list(node->redi);
}

static void	display_indentation(int depth, int *siblings)
{
	int	i;

	i = 0;
	while (i < depth - 1)
	{
		if (siblings[i])
			ft_printf("│   ");
		else
			ft_printf("    ");
		i++;
	}
}

static void	display_tree_recursive(t_node *node, int depth, int isLast,
	int *siblings)
{
	if (!node)
		return ;
	display_indentation(depth, siblings);
	if (depth > 0)
	{
		if (isLast)
			ft_printf("└── ");
		else
			ft_printf("├── ");
	}
	if (!node->left && !node->right)
		display_leaf(node, depth, siblings);
	else
		ft_printf("%s\n", node_type_to_string(node->type));
	if (depth > 0)
		siblings[depth - 1] = !isLast;
	display_tree_recursive(node->left, depth + 1, 0, siblings);
	display_tree_recursive(node->right, depth + 1, 1, siblings);
	if (depth > 0)
		siblings[depth - 1] = 0;
}

void	display_tree(t_node *node)
{
	int	siblings[128];
	int	i;

	i = 0;
	while (i < 128)
	{
		siblings[i] = 0;
		i++;
	}
	display_tree_recursive(node, 0, 1, siblings);
}
