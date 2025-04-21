/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:27:12 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/19 00:27:13 by vbronov          ###   ########.fr       */
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
