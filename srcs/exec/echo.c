/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:48:48 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/28 22:26:19 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char *str, bool nl);

int	ft_echo(char *str, bool nl)
{
	size_t	printed;
	char	*escaped_nl;

	printed = 0;
	if (!str && !nl)
		return (EXIT_SUCCESS);
	else if (!str && nl)
		return (ft_printf("\n") == 2);
	escaped_nl = ft_str_replace(str, "\n", "\\n");
	if (!escaped_nl)
		ft_custom_error_exit("Minishell: echo: memory allocation had failed");
	if (str && nl)
		printed = ft_printf("%s\n", escaped_nl);
	if (str && !nl)
		printed = ft_printf("%s", escaped_nl);
	if (printed == (ft_strlen(escaped_nl) + (int)nl))
		return (free(escaped_nl), EXIT_SUCCESS);
	else
		return (free(escaped_nl), EXIT_FAILURE);
}
