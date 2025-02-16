/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_isin_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:00:52 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_isin_int(t_list **lst, int elem);

t_list	*ft_lst_isin_int(t_list **lst, int elem)
{
	t_list	*current;

	if (!lst)
		return (NULL);
	current = *lst;
	while (current)
	{
		if (current->i == elem)
			return (current);
		current = current->next;
	}
	return (NULL);
}
