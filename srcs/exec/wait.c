/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 22:24:53 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/17 03:24:50 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: verify what we should print for SIGSTOP and SIGTERM
int	wait_pid(t_data *data, int child_pid)
{
	int	pid_tmp;
	int	status;

	pid_tmp = waitpid(child_pid, &status, 0);
	if (pid_tmp == -1)
		ft_error(data, "waitpid");
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		data->exit_status = 128 + WTERMSIG(status);
		if (data->exit_status == 130)
			ft_fprintf(STDERR_FILENO, "\n");
		if (data->exit_status == 131)
			ft_fprintf(STDERR_FILENO, "Quit (core dumped)\n");
	}
	else if (WIFSTOPPED(status))
		data->exit_status = 128 + WSTOPSIG(status);
	else
		ft_fprintf(STDERR_FILENO, "Child process terminated abnormally\n");
	return (data->exit_status);
}
