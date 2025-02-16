/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:01:49 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstcut(t_list **lst, void (*del)(void *), int start, int end);

void	ft_lstcut(t_list **lst, void (*del)(void *), int start, int end)
{
	t_list	*todel_start;
	t_list	*todel_end;

	if (!lst || end <= start || start < 0)
		return ;
	todel_start = ft_lst_getn(lst, start);
	if (!todel_start)
		return ;
	todel_end = ft_lst_getn(lst, end - 1);
	if (start)
		(ft_lst_getn(lst, start - 1))->next = ft_lst_getn(lst, end);
	else if (ft_lst_getn(lst, end))
		*lst = ft_lst_getn(lst, end);
	else
		return ;
	if (todel_end)
		todel_end->next = NULL;
	ft_lstclear(&todel_start, del);
	return ;
}
