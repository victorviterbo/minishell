/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:13:45 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/21 13:46:20 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipe(t_data *data, int pipefds[2])
{
	pipefds[PIPE_IN] = -1;
	pipefds[PIPE_OUT] = -1;
	if (pipe(pipefds) == -1)
	{
		ft_error(data, "pipe");
		return (data->exit_status);
	}
	return (EXIT_SUCCESS);
}

void	close_pipe(t_data *data, int pipe[2])
{
	if (pipe[PIPE_OUT] != -1 && close(pipe[PIPE_OUT]) == -1)
		ft_error(data, "close");
	pipe[PIPE_OUT] = -1;
	if (pipe[PIPE_IN] != -1 && close(pipe[PIPE_IN]) == -1)
		ft_error(data, "close");
	pipe[PIPE_IN] = -1;
}

int	handle_pipex(t_data *data, t_node *node)
{
	int	pid_left;
	int	pid_right;
	int	pipefds[2];

	if (init_pipe(data, pipefds) != EXIT_SUCCESS)
		return (data->exit_status);
	pid_left = create_pipe_process(data, node->left, pipefds, STDOUT_FILENO);
	if (pid_left == -1)
	{
		close_pipe(data, pipefds);
		return (data->exit_status);
	}
	pid_right = create_pipe_process(data, node->right, pipefds, STDIN_FILENO);
	if (pid_right == -1)
	{
		close_pipe(data, pipefds);
		return (data->exit_status);
	}
	close_pipe(data, pipefds);
	wait_pid(data, pid_left);
	return (wait_pid(data, pid_right));
}
