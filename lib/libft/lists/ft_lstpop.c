/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:42:01 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/21 12:59:24 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop(t_list **lst, t_list *node, void (*del)(void *));

void	ft_lstpop(t_list **lst, t_list *node, void (*del)(void *))
{
	t_list	*current;
	t_list	*last;

	current = *lst;
	if (current == node)
	{
		*lst = current->next;
		ft_lstdelone(current, del);
		return ;
	}
	while (current)
	{
		if (current == node)
		{
			last->next = current->next;
			ft_lstdelone(current, del);
			return ;
		}
		last = current;
		current = current->next;
	}
	return ;
}
