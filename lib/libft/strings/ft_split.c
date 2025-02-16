/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:02:00 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_split(char const *s, char c);
static int	count_segments(char const *s, char c);
static int	go_to_next(const char *s, char c, size_t i, int is_c);

char	**ft_split(char const *s, char c)
{
	char	**strarray;
	size_t	i;
	size_t	start;
	size_t	k;

	strarray = ft_calloc(count_segments(s, c) + 1, sizeof(char *));
	if (!strarray)
		return (NULL);
	i = 0;
	k = 0;
	while (*(s + i))
	{
		i = go_to_next(s, c, i, 1);
		if (!*(s + i))
			break ;
		start = i;
		i = go_to_next(s, c, i, 0);
		*(strarray + k) = ft_substr(s, start, i - start);
		if (!*(strarray + k))
			return (ft_free_array((void **)strarray, k), NULL);
		k++;
	}
	*(strarray + k) = NULL;
	return (strarray);
}

static int	count_segments(char const *s, char c)
{
	unsigned int	count;
	unsigned char	uc;
	unsigned char	*us;
	size_t			i;

	i = 0;
	uc = (unsigned char)c;
	us = (unsigned char *)s;
	while (*(us + i) && *(us + i) == uc)
		i++;
	count = (*(us + i) != '\0');
	while (*(us + i))
	{
		if (*(us + i) == uc && *(us + i + 1) && *(us + i + 1) != uc)
			count++;
		i++;
	}
	return (count);
}

static int	go_to_next(const char *s, char c, size_t i, int is_c)
{
	if (is_c)
	{
		while (*(s + i) && *(s + i) == c)
			i++;
	}
	else
	{
		while (*(s + i) && *(s + i) != c)
			i++;
	}
	return (i);
}
