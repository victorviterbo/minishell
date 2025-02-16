/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:07:01 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*(dst + i))
		i++;
	if (i < dstsize)
	{
		while (*(src + j) && i + 1 < dstsize)
		{
			*(dst + i) = *(src + j);
			i++;
			j++;
		}
		*(dst + i) = '\0';
		while (*(src + j))
		{
			i++;
			j++;
		}
		return (i);
	}
	return (dstsize + ft_strlen((char *)src));
}
