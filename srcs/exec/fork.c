/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 22:08:39 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/14 22:09:33 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe_process(t_data *data, t_node *node, int *pipefds, int fd_dst)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (fd_dst == STDOUT_FILENO)
			dup2(pipefds[PIPE_IN], STDOUT_FILENO);
		else
			dup2(pipefds[PIPE_OUT], STDIN_FILENO);
		close_pipe(data, pipefds);
		ft_run_ast(data, node);
		free_all(data);
		exit(data->exit_status);
	}
	else if (pid < 0)
	{
		ft_error(data, "fork");
		return (-1);
	}
	return (pid);
}
