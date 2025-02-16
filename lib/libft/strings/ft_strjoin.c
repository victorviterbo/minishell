/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:56:49 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*joined;
	unsigned int	i;
	unsigned int	j;

	joined = ft_calloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1,
			sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (*(s1 + i))
	{
		*(joined + j) = *(s1 + i);
		i++;
		j++;
	}
	i = 0;
	while (*(s2 + i))
	{
		*(joined + j) = *(s2 + i);
		i++;
		j++;
	}
	*(joined + j) = '\0';
	return (joined);
}
