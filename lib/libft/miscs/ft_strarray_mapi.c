/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_mapi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:49:57 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarray_mapi(char **strarray, char *(*f)(const char *));

char	**ft_strarray_mapi(char **strarray, char *(*f)(const char *))
{
	size_t	i;
	char	**newarray;

	i = 0;
	if (!strarray || !*strarray)
		return (NULL);
	newarray = ft_calloc(ft_arrlen(strarray) + 1, sizeof(char *));
	if (!newarray)
		return (NULL);
	while (*(strarray + i))
	{
		*(newarray + i) = f(*(strarray + i));
		if (!*(newarray + i))
			return (ft_free_array((void **)newarray, i), NULL);
		i++;
	}
	*(newarray + i) = NULL;
	return (newarray);
}
