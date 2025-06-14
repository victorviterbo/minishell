/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:27:12 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/21 13:12:21 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_str_to_arr(char *str);

char	**ft_str_to_arr(char *str)
{
	char	**arr;

	arr = ft_calloc(2, sizeof(char *));
	if (!arr)
		return (NULL);
	arr[0] = str;
	arr[1] = NULL;
	return (arr);
}
