/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:41:42 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/31 00:24:31 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_data *data, const char *message)
{
	if (data && errno)
		data->exit_status = errno;
	if (!message)
		message = DEFAULT_ERROR;
	ft_printf("%s: ", SHELL_NAME);
	if (data->exit_status)
	{
		ft_printf("%s: %s\n", message, strerror(data->exit_status));
	}
	else
		ft_printf("%s\n", message);
	if (data->exit_status == EXIT_SUCCESS)
		data->exit_status = EXIT_FAILURE;
}
