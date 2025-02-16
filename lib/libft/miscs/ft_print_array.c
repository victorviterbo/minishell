/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:09:07 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_array(char **arr, bool nl);

void	ft_print_array(char **arr, bool nl)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (nl)
			ft_printf("%s\n", arr[i]);
		else
			ft_printf("%s", arr[i]);
		i++;
	}
	return ;
}
