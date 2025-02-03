/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:41:42 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/03 16:26:03 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror_exit(const char *message)
{
	if (!message)
		ft_custom_error_exit("Minishell: an unkown error has occured\n");
	perror(message);
	exit(EXIT_FAILURE);
}

void	ft_custom_error_exit(const char *message)
{
	if (!message)
		ft_custom_error_exit("Minishell: an unkown error has occured\n");
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}

void	ft_print_error(const char *message)
{
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
	exit (EXIT_FAILURE);
}
//veux tu verifier si les retour de write sont bien pris en compte ?
//pourquoi tu utilise printf pour error handling et pas write ou ft_putstr_fd ?