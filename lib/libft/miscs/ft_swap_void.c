/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_void.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:32:56 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap_void(void **ptr1, void **ptr2);

void	ft_swap_void(void **ptr1, void **ptr2)
{
	void	*tmp_ptr;

	tmp_ptr = *ptr1;
	*ptr1 = *ptr2;
	*ptr1 = tmp_ptr;
	return ;
}
