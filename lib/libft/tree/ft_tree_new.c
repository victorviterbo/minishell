/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:56:36 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 18:28:57 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tree	*ft_tree_new(void *content);

t_tree	*ft_tree_new(void *content)
{
	t_tree	*newtree;

	newtree = ft_calloc(1, sizeof(t_tree));
	if (!newtree)
		return (NULL);
	newtree->content = content;
	newtree->parent = NULL;
	newtree->left = NULL;
	newtree->right = NULL;
	return (newtree);
}
