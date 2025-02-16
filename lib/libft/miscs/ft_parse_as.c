/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_as.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:26:25 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 20:19:46 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_parse_as(void *ptr, t_Datatype dtype);

double	ft_parse_as(void *ptr, t_Datatype dtype)
{
	double	val;

	if (dtype == SHORT)
		val = (double)*(short *)ptr;
	else if (dtype == INT)
		val = (double)*(int *)ptr;
	else if (dtype == FLOAT)
		val = (double)*(float *)ptr;
	else if (dtype == DOUBLE)
		val = (double)*(double *)ptr;
	else
		val = 0;
	return (val);
}
