/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coalesce_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:34:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_coalesce_char(char *str, char c, bool inplace);
static char	**init(char *str, char c, char **coalesc, char **cstr);

char	*ft_coalesce_char(char *str, char c, bool inplace)
{
	char	*coalesc;
	char	*cstr;
	char	**arr;
	size_t	i;

	if (!str)
		return (NULL);
	arr = init(str, c, &coalesc, &cstr);
	if (inplace)
		free(str);
	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i + 1])
	{
		coalesc = ft_strjoin_ip(coalesc, arr[i], FREE_S1);
		coalesc = ft_strjoin_ip(coalesc, cstr, FREE_S1);
		if (!coalesc)
			return (ft_free_array((void **)arr, ft_arrlen(arr)), free(cstr),
				NULL);
		i++;
	}
	coalesc = ft_strjoin_ip(coalesc, arr[i], FREE_S1);
	ft_free_array((void **)arr, ft_arrlen(arr));
	return (free(cstr), coalesc);
}

static char	**init(char *str, char c, char **coalesc, char **cstr)
{
	char	**arr;

	*coalesc = ft_calloc(1, sizeof(char));
	if (!*coalesc)
		return (NULL);
	*cstr = ft_ctoa(c);
	if (!*cstr)
		return (free(*coalesc), NULL);
	arr = ft_split(str, c);
	if (!arr)
		return (free(*coalesc), free(*cstr), NULL);
	return (arr);
}
