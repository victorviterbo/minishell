/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 03:18:16 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/21 21:00:48 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_next_token(t_data *data, t_token *next, int heredoc_fd)
{
	if (!next)
	{
		ft_error(data, "syntax error near unexpected token 'newline'");
		data->exit_status = EXIT_NUMARG;
		if (heredoc_fd != -1)
			close(heredoc_fd);
		return (EXIT_FAILURE);
	}
	if (next->type != WORD)
	{
		ft_fprintf(STDERR_FILENO,
			"%s: syntax error near unexpected token `%s'\n",
			SHELL_NAME, next->str);
		data->exit_status = EXIT_NUMARG;
		if (heredoc_fd != -1)
			close(heredoc_fd);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	redir_error(int heredoc_fd)
{
	if (heredoc_fd != -1)
		close(heredoc_fd);
	return (EXIT_FAILURE);
}

int	handle_ambiguous_redirect(t_data *data, t_token *token,
	char **parsed, int heredoc_fd)
{
	ft_fprintf(STDERR_FILENO, "%s: %s: ambiguous redirect\n",
		SHELL_NAME, token->str);
	data->exit_status = EXIT_FAILURE;
	ft_free_array((void **)parsed, ft_arrlen(parsed));
	return (redir_error(heredoc_fd));
}
