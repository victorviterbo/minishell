/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_void.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:34:45 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap_void(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list	*ft_lstmap_void(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*current;
	void	*fcontent;

	if (!lst)
		return (NULL);
	fcontent = f(lst->content);
	if (!fcontent)
		return (NULL);
	new_lst = ft_lstnew_void(fcontent);
	if (!new_lst)
		return (free(fcontent), NULL);
	current = new_lst;
	while (lst->next)
	{
		lst = lst->next;
		fcontent = f(lst->content);
		if (!fcontent)
			return (ft_lstclear(&new_lst, del), NULL);
		current->next = ft_lstnew_void(fcontent);
		if (!(current->next))
			return (ft_lstclear(&new_lst, del), free(fcontent), NULL);
		current = current->next;
	}
	return (new_lst);
}
