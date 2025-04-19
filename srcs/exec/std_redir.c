/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 01:51:13 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/19 01:53:06 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_std_streams(t_data *data)
{
	data->saved_streams[0] = dup(STDIN_FILENO);
	if (data->saved_streams[0] == -1)
		return (ft_error(data, "dup"), data->exit_status);
	data->saved_streams[1] = dup(STDOUT_FILENO);
	if (data->saved_streams[1] == -1)
	{
		close(data->saved_streams[0]);
		data->saved_streams[0] = -1;
		return (ft_error(data, "dup"), data->exit_status);
	}
	return (EXIT_SUCCESS);
}

int	restore_std_streams(t_data *data, int saved_streams[2])
{
	if (dup2(saved_streams[0], STDIN_FILENO) == -1)
		return (ft_error(data, "dup2"), data->exit_status);
	if (dup2(saved_streams[1], STDOUT_FILENO) == -1)
		return (ft_error(data, "dup2"), data->exit_status);
	return (EXIT_SUCCESS);
}
