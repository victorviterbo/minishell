/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_strocc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:05:58 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_strocc(char *str, char *to_count, bool distinct);

int	ft_count_strocc(char *str, char *to_count, bool distinct)
{
	int		count;
	int		i;
	size_t	to_count_len;

	i = 0;
	count = 0;
	if (!str || !to_count)
		return (-1);
	to_count_len = ft_strlen(to_count);
	if (to_count_len == 0)
		return (1);
	if (ft_strlen(str) < to_count_len)
		return (0);
	while (str[i])
	{
		if (ft_strncmp(str + i, to_count, to_count_len) == 0)
		{
			count++;
			i += ((to_count_len - 1) * distinct) + 1;
		}
		else
			i++;
	}
	return (count);
}
