/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/06 20:24:55 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	if (ft_echo("print this string with newline", true) != 0)
		return (EXIT_FAILURE);
	if (ft_echo("print this string without newline", false) != 0)
		return (EXIT_FAILURE);
	if (ft_echo("print this string \n with newline", true) != 0)
		return (EXIT_FAILURE);
	if (ft_echo(NULL, false) != 0)
		return (EXIT_FAILURE);
	if (ft_echo(NULL, true) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
