/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:48:48 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/25 19:07:34 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char *str, bool no_nl);

int	ft_echo(char *str, bool no_nl)
{
	char	*escaped_nl;
	size_t	printed;

	printed = 0;
	escaped_nl = ft_str_replace(str, "\n", "\\n");
	if (!escaped_nl)
		return (EXIT_FAILURE);
	if (!str && !no_nl)
		printed = ft_printf("\n");
	else if (str && no_nl)
		printed = ft_printf("%s", escaped_nl);
	else if (str)
		printed = ft_printf("%s\n", escaped_nl);
	if (printed == (ft_strlen(escaped_nl) + 2 * (!no_nl)))
		return (free(escaped_nl), EXIT_SUCCESS);
	else
		return (free(escaped_nl), EXIT_FAILURE);
}
