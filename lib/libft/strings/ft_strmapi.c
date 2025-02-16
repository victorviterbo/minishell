/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 21:41:57 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char));

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char	*new_str;
	size_t	i;

	i = 0;
	new_str = ft_calloc((ft_strlen((char *)s) + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	while (*(s + i))
	{
		*(new_str + i) = f(i, *(s + i));
		i++;
	}
	*(new_str + i) = '\0';
	return (new_str);
}
