/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:41:42 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/17 21:47:15 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_perror_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	ft_custom_error_exit(const char *message)
{
	ft_printf(message);
	exit(EXIT_FAILURE);
}
