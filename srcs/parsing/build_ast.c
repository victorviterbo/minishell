/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:47:44 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/19 15:53:10 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*skip_parenthesis(t_data *data, t_token *token)
{
	int	scope;

	scope = 0;
	while (token)
	{
		if (token->type == OPENPAR)
			scope++;
		else if (token->type == CLOSEPAR && --scope == 0)
			return (token);
		token = token->next;
	}
	if (scope > 0)
		return (ft_error(data, "syntax error near unexpected token `('"), \
				data->exit_status = EXIT_NUMARG, NULL);
	if (scope < 0)
		return (ft_error(data, "syntax error near unexpected token `)'"), \
				data->exit_status = EXIT_NUMARG, NULL);
	return (NULL);
}

t_token	*search_operator(t_data *data, t_token *start, t_token *end)
{
	t_token	*token;
	t_token	*saved_token;

	saved_token = NULL;
	token = start;
	while (token != end)
	{
		if (token->type == OPENPAR)
			token = skip_parenthesis(data, token);
		else if (token->type == OR || token->type == AND)
			saved_token = token;
		if (token == NULL)
			break ;
		token = token->next;
	}
	return (saved_token);
}

t_token	*search_pipe(t_data *data, t_token *start, t_token *end)
{
	t_token	*token;
	t_token	*saved_token;

	saved_token = NULL;
	token = start;
	while (token != end)
	{
		if (token->type == OPENPAR)
			token = skip_parenthesis(data, token);
		else if (token->type == PIPE)
		{
			saved_token = token;
			break ;
		}
		if (token == NULL)
			break ;
		token = token->next;
	}
	return (saved_token);
}

t_node	*handle_parenthesis(t_data *data, t_token *start)
{
	t_node	*new_node;
	t_token	*end;

	new_node = new_tree_node(data, OPENPAR);
	if (!new_node)
		return (NULL);
	end = skip_parenthesis(data, start);
	if (end == NULL)
		return (free_tree(new_node), NULL);
	new_node->left = build_tree(data, start->next, end);
	if (!new_node->left)
		return (free_tree(new_node), NULL);
	return (new_node);
}

t_node	*build_tree(t_data *data, t_token *start, t_token *end)
{
	t_token			*op_token;

	if (start == NULL)
		return (NULL);
	op_token = search_operator(data, start, end);
	if (data->exit_status)
		return (NULL);
	if (op_token)
		return (handle_operator(data, start, end, op_token));
	op_token = search_pipe(data, start, end);
	if (data->exit_status)
		return (NULL);
	if (op_token)
		return (handle_operator(data, start, end, op_token));
	if (start->type == OPENPAR)
		return (handle_parenthesis(data, start));
	return (handle_cmd(data, start, end));
}
