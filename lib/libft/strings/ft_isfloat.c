/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:32:18 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isfloat(char *str);

int	ft_isfloat(char *str)
{
	char	**int_dec;
	int		is_floatable;

	is_floatable = 0;
	if (!str)
		return (is_floatable);
	int_dec = ft_split(str, '.');
	if (ft_arrlen(int_dec) == 1)
	{
		is_floatable = ft_isint(int_dec[0]);
		ft_free_array((void **)int_dec, 1);
		return (is_floatable);
	}
	if (ft_arrlen(int_dec) == 2)
	{
		is_floatable = (ft_isint(int_dec[0]) * ft_isint(int_dec[1]));
		ft_free_array((void **)int_dec, 2);
		return (is_floatable);
	}
	ft_free_array((void **)int_dec, ft_arrlen(int_dec));
	return (is_floatable);
}
