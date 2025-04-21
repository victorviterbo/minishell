/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 03:00:21 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/21 21:00:23 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_and(t_data *data, t_node *node)
{
	int	ret;

	if (!node || !node->left || !node->right)
	{
		ft_error(data, "syntax error near unexpected token '&&'");
		return (EXIT_FAILURE);
	}
	ret = ft_run_ast(data, node->left);
	if (ret == EXIT_SUCCESS)
	{
		data->last_exit_status = ret;
		data->exit_status = EXIT_SUCCESS;
		return (ft_run_ast(data, node->right));
	}
	return (ret);
}

static int	handle_or(t_data *data, t_node *node)
{
	int	ret;

	if (!node || !node->left || !node->right)
	{
		ft_error(data, "syntax error near unexpected token '||'");
		return (EXIT_FAILURE);
	}
	ret = ft_run_ast(data, node->left);
	if (ret != EXIT_SUCCESS)
	{
		data->last_exit_status = ret;
		data->exit_status = EXIT_SUCCESS;
		return (ft_run_ast(data, node->right));
	}
	return (ret);
}

int	handle_command(t_data *data, t_node *node)
{
	char		**args;
	t_pfunc		func;

	apply_redirections(data, node->redi);
	if (data->exit_status != EXIT_SUCCESS)
		return (restore_std_streams(data, data->saved_streams),
			data->exit_status);
	args = token_list_to_args(data, node->args);
	if (!args)
		return (restore_std_streams(data, data->saved_streams),
			data->exit_status);
	func = is_builtin(args[0], data->builtins);
	if (func)
		data->exit_status = func(data, args, ft_arrlen(args));
	else if (args[0])
		data->exit_status = exec_non_builtin(data, args);
	ft_free_array((void **)args, ft_arrlen(args));
	restore_std_streams(data, data->saved_streams);
	return (data->exit_status);
}

int	handle_openpar(t_data *data, t_node *node)
{
	int	pid;
	int	exit_status;

	pid = fork();
	if (pid == -1)
		return (ft_error(data, "fork"), data->exit_status);
	if (pid == 0)
	{
		exit_status = ft_run_ast(data, node->left);
		free_all(data);
		exit(exit_status);
	}
	return (wait_pid(data, pid));
}

int	ft_run_ast(t_data *data, t_node *node)
{
	if (!node)
		return (EXIT_SUCCESS);
	if (node->type == AND)
		return (handle_and(data, node));
	if (node->type == OR)
		return (handle_or(data, node));
	if (node->type == PIPE)
		return (handle_pipex(data, node));
	if (node->type == OPENPAR)
		return (handle_openpar(data, node));
	return (handle_command(data, node));
}
