/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_stream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:18:43 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/09 14:02:18 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_stream(t_data *data, t_leaf *leaf, t_token *token)
{
	int	fd;

	if (token->type == STDIN)
		fd = open(token->str, O_RDONLY);
	else if (token->type == STDIN_HEREDOC)
		fd = 1;
	else if (token->type == STDOUT)
		fd = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (token->type == STDOUT_APPEND)
		fd = open(token->str, O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		ft_fprintf(STDERR_FILENO, "open: %s\n", strerror(errno));
	else if (token->type == STDIN || token->type == STDIN_HEREDOC)
	{
		if (leaf->fdin != 0)
			close(leaf->fdin);
		leaf->fdin = fd;
	}
	else if (token->type == STDOUT || token->type == STDOUT_APPEND)
	{
		if (leaf->fdout != 0)
			close(leaf->fdout);
		leaf->fdout = fd;
	}
	return (fd);
}
