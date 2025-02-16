/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:28:28 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa_base(long long n, char *base);
static size_t	handle_neg(long long *number, char *number_str);

char	*ft_itoa_base(long long n, char *base)
{
	char		*number_str;
	size_t		magnitude;
	size_t		i;
	long long	number;

	if (ft_strlen(base) < 2)
		return (NULL);
	number = n;
	number_str = ft_calloc((ft_number_len(number, ft_strlen(base)) + 2),
			sizeof(char));
	if (!number_str)
		return (NULL);
	i = handle_neg(&number, number_str);
	magnitude = ft_prev_power(number, ft_strlen(base));
	while (magnitude)
	{
		number_str[i] = *(base + number / magnitude);
		number %= magnitude;
		magnitude /= ft_strlen(base);
		i++;
	}
	number_str[i] = '\0';
	return (number_str);
}

static size_t	handle_neg(long long *number, char *number_str)
{
	if (*number < 0)
	{
		*(number_str) = '-';
		*number = -(*number);
		return (1);
	}
	else
		return (0);
}
