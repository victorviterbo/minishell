/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:38:10 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/17 19:31:26 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_node_redirs(t_data *data, t_token *start, t_node *cmd_node, \
	t_token *op_token)
{
	t_token	*file_token;

	if (start->next->type != WORD)
	{
		ft_fprintf(STDERR_FILENO, "%s: syntax error near unexpected \
token '%s'\n", SHELL_NAME, start->next->str);
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

static int	init_cmd_node(t_data *data, t_token *start, t_token *end,
	t_node *cmd_node)
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
