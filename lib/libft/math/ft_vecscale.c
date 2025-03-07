/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecscale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 22:06:06 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_coor	ft_vecscale(t_coor base, t_coor tip, float scale);

t_coor	ft_vecscale(t_coor base, t_coor tip, float scale)
{
	t_coor	new_vector;

	new_vector.x = (tip.x - base.x) * (double)scale + base.x;
	new_vector.y = (tip.y - base.y) * (double)scale + base.y;
	new_vector.z = (tip.z - base.z) * (double)scale + base.z;
	return (new_vector);
}
