/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dotprod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:17:30 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_dotprod(t_coor v1, t_coor v2);

double	ft_dotprod(t_coor v1, t_coor v2)
{
	double	dot_product;

	dot_product = (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	return (dot_product);
}
