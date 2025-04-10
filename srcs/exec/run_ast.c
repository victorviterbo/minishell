/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 03:00:21 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/09 19:20:57 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_and(t_data *data, t_node *node)
{
	int	ret;

	if (!node || !node->left || !node->right)
	{
		ft_error(data, "syntax error near unexpected token 'AND'");
		return (EXIT_FAILURE);
	}
	ret = ft_run_ast(data, node->left);
	if (ret == EXIT_SUCCESS)
		return (ft_run_ast(data, node->right));
	return (ret);
}

static int	handle_or(t_data *data, t_node *node)
{
	int	ret;

	if (!node || !node->left || !node->right)
	{
		ft_error(data, "syntax error near unexpected token 'OR'");
		return (EXIT_FAILURE);
	}
	ret = ft_run_ast(data, node->left);
	if (ret == EXIT_FAILURE)
		return (ft_run_ast(data, node->right));
	return (ret);
}

int	handle_command(t_data *data, t_node *node)
{
	char		**args;
	t_pfunc		func;

	args = token_list_to_args(data, node->args);
	if (!args)
		return (data->exit_status);
	func = is_builtin(args[0], data->builtins);
	if (func)
	{
		data->exit_status = func(data, args, ft_arrlen(args));
	}
	ft_free_array((void **)args, ft_arrlen(args));
	// TODO: add non builtin func handling
	return (data->exit_status);
}

int	ft_run_ast(t_data *data, t_node *node)
{
	if (!node)
		return (EXIT_SUCCESS);
	if (node->type == AND)
		return (handle_and(data, node));
	if (node->type == OR)
		return (handle_or(data, node));
	// if (node->type == PIPE)
	//     return (handle_pipex(data, node));
	//TODO: handle openpar?
	// if (node->type == OPENPAR)
	//     return (handle_openpar(data, node));
	return (handle_command(data, node));
}
