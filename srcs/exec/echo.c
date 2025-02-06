/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:48:48 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/04 19:29:27 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char *str, bool nl);

int	ft_echo(char *str, bool nl)
{
	size_t	printed;

	printed = 0;
	if (!str && !nl)
		return (EXIT_SUCCESS);
	else if (!str && nl)
		return (ft_printf("\n") == 2);
	if (!str)
		ft_print_error("echo: memory allocation had failed");
	if (str && nl)
		printed = ft_printf("%s\n", str);
	if (str && !nl)
		printed = ft_printf("%s", str);
	if (printed == (ft_strlen(str) + (int)nl))
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
