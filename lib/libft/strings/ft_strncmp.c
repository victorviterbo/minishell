/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:37:16 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n);

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ucs1;
	unsigned char	*ucs2;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	i = 0;
	ucs1 = (unsigned char *)s1;
	ucs2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (*(s1 + i) && *(s2 + i) && i < n - 1)
	{
		if (*(s1 + i) != *(s2 + i))
			return ((*(ucs1 + i) > *(ucs2 + i)) - (*(ucs1 + i) < *(ucs2 + i)));
		i++;
	}
	return ((*(ucs1 + i) > *(ucs2 + i)) - (*(ucs1 + i) < *(ucs2 + i)));
}
