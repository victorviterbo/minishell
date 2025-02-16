/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmaxi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:30:28 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstmaxi(t_list **lst);

int	ft_lstmaxi(t_list **lst)
{
	int		max;
	t_list	*current;

	if (!lst || !*lst)
		return (0);
	current = *lst;
	max = current->i;
	current = current->next;
	while (current)
	{
		max = ft_max(max, current->i);
		current = current->next;
	}
	return (max);
}
