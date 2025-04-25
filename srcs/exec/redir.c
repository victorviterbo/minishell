/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 07:38:41 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/25 14:13:20 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_redirection(t_data *data, t_token *token, t_token *next,
	int *heredoc_fd)
{
	if (token->type == STDIN_HEREDOC)
	{
		if (handle_heredoc_redirection(data, next, heredoc_fd))
			return (EXIT_FAILURE);
	}
	else if (token->type == STDIN)
	{
		if (handle_stdin_redirection(data, next, heredoc_fd))
			return (EXIT_FAILURE);
	}
	else if (token->type == STDOUT)
	{
		if (handle_stdout_redirection(data, next, heredoc_fd, FALSE))
			return (EXIT_FAILURE);
	}
	else if (token->type == STDOUT_APPEND)
	{
		if (handle_stdout_redirection(data, next, heredoc_fd, TRUE))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	apply_redirections(t_data *data, t_token *token)
{
	t_token	*next;
	int		heredoc_fd;
	int		error;

	heredoc_fd = -1;
	if (!token)
		return ;
	while (token)
	{
		next = token->next;
		if (check_next_token(data, next, heredoc_fd) == EXIT_FAILURE)
			return ;
		error = process_redirection(data, token, next, &heredoc_fd);
		if (error)
			return ;
		token = next->next;
	}
	if (heredoc_fd != -1)
	{
		if (dup2(heredoc_fd, STDIN_FILENO) == -1)
			ft_error(data, "dup2");
		close(heredoc_fd);
	}
}
