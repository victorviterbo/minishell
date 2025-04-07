/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:47:44 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/06 23:04:37 by vbronov          ###   ########.fr       */
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
		return (ft_error(data, "syntax error near unexpected token ')'"), \
				data->exit_status = EXIT_NUMARG, NULL);
	if (scope < 0)
		return (ft_error(data, "syntax error near unexpected token '('"), \
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

t_node	*handle_operator(t_data *data, t_token *start, t_token *end, \
	t_token *op_token)
{
	t_node			*new_node;

	new_node = new_tree_node(data, op_token->type);
	if (!new_node)
		return (NULL);
	new_node->left = build_tree(data, start, op_token);
	if (!new_node->left)
		return (free_tree(new_node), NULL);
	new_node->right = build_tree(data, op_token->next, end);
	if (!new_node->right)
		return (free_tree(new_node), NULL);
	return (new_node);
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

int	init_node_redirs(t_data *data, t_token *start, t_node *cmd_node, \
	t_token *op_token)
{
	t_token	*file_token;

	if (start->next->type != WORD)
	{
		ft_fprintf(STDERR_FILENO, "syntax error near unexpected token '%s'\n", \
			start->next->str);
		data->exit_status = EXIT_NUMARG;
		return (FALSE);
	}
	file_token = copy_token(data, start->next);
	if (!file_token)
		return (FALSE);
	push_back_token(&cmd_node->redi, op_token);
	push_back_token(&cmd_node->redi, file_token);
	return (TRUE);
}

int	init_cmd_node(t_data *data, t_token *start, t_token *end, t_node *cmd_node)
{
	t_token	*token;

	while (start != end)
	{
		token = copy_token(data, start);
		if (!token)
			return (FALSE);
		if (start->type >= STDOUT && start->type <= STDIN_HEREDOC)
		{
			if (start->next == NULL || start->next == end)
			{
				ft_error(data, "syntax error near unexpected token 'newline'");
				data->exit_status = EXIT_NUMARG;
				return (free(token->str), free(token), FALSE);
			}
			if (!init_node_redirs(data, start, cmd_node, token))
				return (free(token->str), free(token), FALSE);
			start = start->next;
		}
		else if (start->type == WORD)
			push_back_token(&cmd_node->args, token);
		start = start->next;
	}
	return (TRUE);
}

t_node	*handle_cmd(t_data *data, t_token *start, t_token *end)
{
	t_node	*new_node;

	new_node = new_tree_node(data, CMD);
	if (!new_node)
		return (NULL);
	if (!init_cmd_node(data, start, end, new_node))
		return (free_tree(new_node), NULL);
	return (new_node);
}

t_node	*build_tree(t_data *data, t_token *start, t_token *end)
{
	t_token			*op_token;

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
