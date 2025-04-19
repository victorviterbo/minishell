/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 03:00:21 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/18 19:29:18 by vbronov          ###   ########.fr       */
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

	args = token_list_to_args(data, node->args);
	if (!args)
		return (data->exit_status);
	apply_redirections(data, node->redi);
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

	pid = fork();
	if (pid == -1)
		return (ft_error(data, "fork"), data->exit_status);
	if (pid == 0)
	{
		data->exit_status = ft_run_ast(data, node->left);
		free_all(data);
		exit(data->exit_status);
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
