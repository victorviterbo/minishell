/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:41:42 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/25 14:55:05 by vviterbo         ###   ########.fr       */
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

int	check_file_error(t_data *data, char **parsed, char type)
{
    struct stat	buffer;

	if (type == 'r' && stat(parsed[0], &buffer) != 0)
	{
		if (errno)
			data->exit_status = errno;
		else
			data->exit_status = EXIT_FAILURE;
		ft_fprintf(STDERR_FILENO, "%s: %s: %s", SHELL_NAME, parsed[0],
			strerror(data->exit_status));
		return (data->exit_status);
	}
	if (type == 'w' && (buffer.st_mode & S_IWUSR))
		return (EXIT_SUCCESS);
	else if ((type == 'w' && !(buffer.st_mode & S_IWUSR))
		|| (type == 'r' && !(buffer.st_mode & S_IRUSR)))
	{
		data->exit_status = EXIT_FAILURE;
		ft_fprintf(STDERR_FILENO, "%s: %s\n", SHELL_NAME, parsed[0], 
			strerror(EXIT_FAILURE));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
