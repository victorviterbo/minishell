/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_isin_void.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:00:52 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_isin_void(t_list **lst, void *elem, int size);

t_list	*ft_lst_isin_void(t_list **lst, void *elem, int size)
{
	t_list	*current;

	if (!lst)
		return (NULL);
	current = *lst;
	while (current)
	{
		if (!elem && !current->content)
			return (current);
		if (elem && size == -1)
		{
			if (!ft_strncmp(current->content, elem, ft_strlen(elem)))
				return (current);
		}
		else if (elem)
		{
			if (!ft_memcmp(current->content, elem, size))
				return (current);
		}
		current = current->next;
	}
	return (NULL);
}
