/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:48:48 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/07 13:12:57 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_data *data, char **args, int argc)
{
	int		i;
	int		nl;
	size_t	printed;

	nl = TRUE;
	i = 1;
	if (argc > 1 && !ft_strcmp(args[1], "-n"))
	{
		nl = FALSE;
		i = 2;
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
