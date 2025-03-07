/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:16:36 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size);

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*bptr;
	size_t			i;

	i = 0;
	if (!count || !size)
		return (malloc(0));
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	bptr = (unsigned char *)ptr;
	while (i < (count * size))
	{
		*(bptr + i) = '\0';
		i++;
	}
	return (ptr);
}
