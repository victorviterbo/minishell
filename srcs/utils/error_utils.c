/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:41:42 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/15 17:54:04 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_data *data, const char *message)
{
	if (data && errno)
		data->exit_status = errno;
	else if (data)
		data->exit_status = EXIT_FAILURE;
	if (!message)
		message = DEFAULT_ERROR;
	write (STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	if (errno)
		perror(message);
	else
	{
		write(STDERR_FILENO, message, ft_strlen(message));
		write(STDERR_FILENO, "\n", 1);
	}
}
