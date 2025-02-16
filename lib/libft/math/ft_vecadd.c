/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:34:17 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_coor	ft_vecadd(t_coor v1, t_coor v2);

t_coor	ft_vecadd(t_coor v1, t_coor v2)
{
	t_coor	new_vector;

	new_vector.x = v1.x + v2.x;
	new_vector.y = v1.y + v2.y;
	new_vector.z = v1.z + v2.z;
	return (new_vector);
}
