/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnicmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:37:16 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/24 19:15:34 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnicmp(const char *s1, const char *s2, size_t n);

int	ft_strnicmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] && s2[i])
	{
		if (ft_tolower(*(s1 + i)) != ft_tolower(*(s2 + i)))
			return ((ft_tolower(s1[i]) > ft_tolower(s2[i]))
				- (ft_tolower(s1[i]) < ft_tolower(s2[i])));
		i++;
	}
	return ((ft_tolower(s1[i]) > ft_tolower(s2[i]))
		- (ft_tolower(s1[i]) < ft_tolower(s2[i])));
}
