/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 03:00:21 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/01 00:51:38 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_node_type(t_tree *node)
{
	t_token	*token;

	if (!node || !node->content)
	{
		return (-1);
	}
	if (!node->left && !node->right)
	{
		return (-1);
	}
	token = (t_token *)node->content;
	return (token->type);
}

static int	handle_and(t_data *data, t_tree *node)
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

static int	handle_or(t_data *data, t_tree *node)
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
int	handle_command(t_data *data, t_leaf *leaf)
{
	char		**args;
	t_pfunc		func;

	args = leaf->args;
	func = is_builtin(args[0], data->builtins);
	if (func)
	{
		data->exit_status = func(data, args, ft_arrlen(args));
	}
	// TODO: add non builtin func handling
	return (data->exit_status);
}

int	ft_run_ast(t_data *data, t_tree *node)
{
	int	type;

	if (!node)
		return (EXIT_SUCCESS);
	type = get_node_type(node);
	if (type == AND)
		return (handle_and(data, node));
	if (type == OR)
		return (handle_or(data, node));
	// if (type == PIPE)
	//     return (handle_pipex(data, node));
	//TODO: handle openpar?
	// if (type == OPENPAR)
	//     return (handle_openpar(data, node));
	return (handle_command(data, node->content));
}
