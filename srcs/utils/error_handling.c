/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:41:42 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/28 20:33:10 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	ft_custom_error_exit(const char *message)
{
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}
