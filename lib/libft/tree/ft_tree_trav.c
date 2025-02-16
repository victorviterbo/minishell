/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_trav.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:05:07 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 20:19:30 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tree_trav(t_tree *node, void(*f)(void *),
		t_Tree_Travel_Type trav_type);

void	ft_tree_trav(t_tree *node, void(*f)(void *),
		t_Tree_Travel_Type trav_type)
{
	if (trav_type == PRE_ORDER)
		f(node->content);
	if (node->left)
		ft_tree_trav(node->left, f, trav_type);
	if (trav_type == IN_ORDER)
		f(node->content);
	if (node->right)
		ft_tree_trav(node->right, f, trav_type);
	if (trav_type == POST_ORDER)
		f(node->content);
	return ;
}
