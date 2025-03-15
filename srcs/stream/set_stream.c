/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_stream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:18:43 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/15 16:21:17 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_stream(t_data *data, t_leaf *leaf, t_token *token);

int	open_stream(t_data *data, t_leaf *leaf, t_token *token)
{
	int	fd;

	fd = 0;
	if (token->type == STDIN)
		fd = open(token->next->str, O_RDONLY);
	else if (token->type == STDIN_HEREDOC)
		leaf->limiter = token->next->str;
	else if (token->type == STDOUT)
		fd = open(token->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (token->type == STDOUT_APPEND)
		fd = open(token->next->str, O_CREAT | O_APPEND, 0644);
	else if (token->type == STDIN || token->type == STDIN_HEREDOC)
	{
		if (leaf->fdin != 0 && close(leaf->fdin) < 0)
			return (ft_error(data, "close: could not close file"), -1);
		leaf->fdin = fd;
	}
	else if (token->type == STDOUT || token->type == STDOUT_APPEND)
	{
		if (leaf->fdout != 0 && close(leaf->fdout) < 0)
			return (ft_error(data, "close: could not close file"), -1);
		leaf->fdout = fd;
	}
	return (fd);
}
