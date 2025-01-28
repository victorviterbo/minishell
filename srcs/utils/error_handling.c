/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:41:42 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/28 22:02:07 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror_exit(const char *message)
{
	if (!message)
		ft_custom_error_exit("Minishell: an unkown error has occured");
	perror(message);
	exit(EXIT_FAILURE);
}

void	ft_custom_error_exit(const char *message)
{
	if (!message)
		ft_custom_error_exit("Minishell: an unkown error has occured");
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}
