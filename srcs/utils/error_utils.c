/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:41:42 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/25 19:28:52 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_data *data, const char *message)
{
	if (data && errno)
		data->exit_status = errno;
	if (!message)
		message = DEFAULT_ERROR;
	ft_fprintf(STDERR_FILENO, "%s: ", SHELL_NAME);
	if (data->exit_status)
		ft_fprintf(STDERR_FILENO, "%s: %s\n", message,
			strerror(data->exit_status));
	else
		ft_fprintf(STDERR_FILENO, "%s\n", message);
	if (data->exit_status == EXIT_SUCCESS)
		data->exit_status = EXIT_FAILURE;
}

void	error_execve_format(t_data *data)
{
	data->exit_status = EXIT_NUMARG;
	ft_fprintf(STDERR_FILENO, ".: filename argument required\n.: usage: . \
		filename [arguments]\n");
	return ;
}
