/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:48:48 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/27 19:13:49 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

int	ft_echo(t_data *data, char **args, int argc)
{
	int		i;
	int		nl;
	size_t	printed;

	nl = TRUE;
	i = 1;
	while (i < argc && is_valid_n_flag(args[i]))
	{
		nl = FALSE;
		i++;
	}
	while (i < argc)
	{
		printed = ft_printf("%s", args[i]);
		if (printed != ft_strlen(args[i]))
			return (ft_error(data, "echo: printing error"), EXIT_FAILURE);
		if (i < argc - 1)
			ft_printf(" ");
		i++;
	}
	if (nl)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
