/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:39:59 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len);

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	*bstr;

	i = 0;
	c = (unsigned int)c;
	bstr = (unsigned char *)str;
	while (i < len)
	{
		*(bstr + i) = c;
		i++;
	}
	return (str);
}
