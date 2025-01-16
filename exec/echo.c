/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:48:48 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/15 17:18:28 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

void	ft_echo(char *str, bool no_nl);

void	ft_echo(char *str, bool no_nl)
{
	char	*escaped_nl;

	
	if (no_nl)
	{
		ft_printf("%s", str);
	}
	else
		ft_printf("%s\n", str);
	return ;
}
