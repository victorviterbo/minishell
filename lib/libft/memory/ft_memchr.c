/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:56:39 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n);

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*bs;

	i = 0;
	bs = (unsigned char *)s;
	c = (unsigned char)c;
	while (i < n)
	{
		if (*(bs + i) == c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
