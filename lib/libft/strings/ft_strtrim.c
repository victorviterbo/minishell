/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:02:38 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s1, char const *set);
static int		ft_is_in_set(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	end = ft_strlen((char *)s1) - (ft_strlen((char *)s1) > 0);
	start = 0;
	while (*(s1 + start) && ft_is_in_set(*(s1 + start), set))
		start++;
	while (end > start && ft_strchr(set, *(s1 + end)))
		end--;
	trimmed = ft_calloc(end - start + 1 + (ft_strlen((char *)s1) > 0),
			sizeof(char));
	if (!(trimmed))
		return (NULL);
	while (*(s1 + start) && start <= end)
	{
		*(trimmed + i) = *(s1 + start);
		i++;
		start++;
	}
	*(trimmed + i) = '\0';
	return (trimmed);
}

static int	ft_is_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}
