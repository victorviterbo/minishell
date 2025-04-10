/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:35:52 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/10 11:44:14 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_array_append(char **array, char *str, bool first);

char	**ft_array_append(char **array, char *str, bool first)
{
	size_t	i;
	char	**concatenated;

	if (!str)
		return (array);
	if (!array)
		return (ft_str_to_arr(str));
	concatenated = ft_calloc(ft_arrlen(array) + 2, sizeof(char *));
	if (!concatenated)
		return (ft_free_array((void **)array, ft_arrlen(array)), NULL);
	i = 0;
	if (first)
		concatenated[0] = str;
	while (array[i])
	{
		concatenated[i + first] = array[i];
		i++;
	}
	if (!first)
		concatenated[i] = str;
	concatenated[i + 1] = NULL;
	free(array);
	return (concatenated);
}
