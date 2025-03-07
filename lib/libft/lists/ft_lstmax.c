/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:30:28 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_lstmax(t_list **lst, int dtype);

double	ft_lstmax(t_list **lst, int dtype)
{
	double	max;
	t_list	*current;

	if (!lst || !*lst)
		return (0);
	current = *lst;
	max = ft_parse_as(current->content, dtype);
	current = current->next;
	while (current)
	{
		max = ft_max(max, ft_parse_as(current->content, dtype));
		current = current->next;
	}
	return (max);
}
