/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnicmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:37:16 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/21 12:07:44 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnicmp(const char *s1, const char *s2, size_t n);

int	ft_strnicmp(const char *s1, const char *s2, size_t n)
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
		if (ft_tolower(*(s1 + i)) != ft_tolower(*(s2 + i)))
			return ((ft_tolower(*(ucs1 + i)) > ft_tolower(*(ucs2 + i)))
				- (ft_tolower(*(ucs1 + i)) < ft_tolower(*(ucs2 + i))));
		i++;
	}
	return ((ft_tolower(*(ucs1 + i)) > ft_tolower(*(ucs2 + i)))
		- (ft_tolower(*(ucs1 + i)) < ft_tolower(*(ucs2 + i))));
}
