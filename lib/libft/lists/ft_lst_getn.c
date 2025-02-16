/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_getn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:24:52 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_getn(t_list **lst, int n);

t_list	*ft_lst_getn(t_list **lst, int n)
{
	int		i;
	t_list	*current;

	i = 0;
	if (!lst)
		return (NULL);
	current = *lst;
	while (current)
	{
		if (i == n)
			return (current);
		current = current->next;
		i++;
	}
	return (NULL);
}
