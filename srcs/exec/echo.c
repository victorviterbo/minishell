/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:48:48 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/15 17:06:54 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_data *data, char *str, bool nl);

void	ft_echo(t_data *data, char *str, bool nl)
{
	size_t	printed;

	printed = 0;
	if (!str && !nl)
		return ;
	else if (!str && nl)
	{
		if (ft_printf("\n") != 2)
			return (ft_error(data, "echo: print to stdout has failed"));
		return ;
	}
	if (!str)
		return (ft_error(data, "echo: memory allocation had failed"));
	if (str && nl)
		printed = ft_printf("%s\n", str);
	if (str && !nl)
		printed = ft_printf("%s", str);
	if (printed == (ft_strlen(str) + (int)nl))
		return ;
	else
		return (ft_error(data, "echo: print to stdout has failed"));
}
