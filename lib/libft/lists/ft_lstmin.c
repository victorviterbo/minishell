/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:40:37 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_lstmin(t_list **lst, int dtype);

double	ft_lstmin(t_list **lst, int dtype)
{
	double	min;
	t_list	*current;

	if (!lst || !*lst)
		return (0);
	current = *lst;
	min = ft_parse_as(current->content, dtype);
	current = current->next;
	while (current)
	{
		min = ft_min(min, ft_parse_as(current->content, dtype));
		current = current->next;
	}
	return (min);
}
