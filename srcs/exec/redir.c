/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 07:38:41 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/27 01:31:07 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_redirection(t_data *data, t_token *token, t_token *next)
{
	if (token->type == STDIN_HEREDOC)
	{
		if (token->heredoc_fd == -1)
			return (ft_error(data, "heredoc: fd not set"), EXIT_FAILURE);
		if (dup2(token->heredoc_fd, STDIN_FILENO) == -1)
			ft_error(data, "dup2");
		close(token->heredoc_fd);
		token->heredoc_fd = -1;
	}
	else if (token->type == STDIN)
	{
		if (handle_stdin_redirection(data, next))
			return (EXIT_FAILURE);
	}
	else if (token->type == STDOUT)
	{
		if (handle_stdout_redirection(data, next, FALSE))
			return (EXIT_FAILURE);
	}
	else if (token->type == STDOUT_APPEND)
	{
		if (handle_stdout_redirection(data, next, TRUE))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	apply_redirections(t_data *data, t_token *token)
{
	t_token	*next;
	int		error;

	if (!token)
		return ;
	while (token)
	{
		next = token->next;
		if (check_next_token(data, next))
			return ;
		error = process_redirection(data, token, next);
		if (error)
			return ;
		token = next->next;
	}
}

void	prepare_heredocs(t_data *data, t_node *node)
{
	t_token	*cur;

	if (!node)
		return ;
	if (node->type == CMD)
	{
		cur = node->redi;
		while (cur)
		{
			if (cur->type == STDIN_HEREDOC)
			{
				if (check_next_token(data, cur->next))
					return ;
				handle_heredoc_redirection(data, cur->next, &cur->heredoc_fd);
				if (cur->heredoc_fd == -1)
					return ;
			}
			cur = cur->next;
		}
	}
	prepare_heredocs(data, node->left);
	prepare_heredocs(data, node->right);
}
