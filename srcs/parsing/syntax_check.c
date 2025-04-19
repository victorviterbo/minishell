/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:10:43 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/19 02:07:54 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	check_ope(t_data *data, t_token *token)
{
	if (!token->next)
		return (ft_error(data, "syntax error near unexpected token `newline'"),
			EXIT_FAILURE);
	else if (is_ope(token->next))
	{
		ft_fprintf(STDERR_FILENO, "%s: syntax error near unexpected \
token `%s'\n", SHELL_NAME, token->next->str);
		data->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static	int	check_par(t_data *data, t_token *token, t_token *last, int *parlvl)
{
	*parlvl += (token->type == OPENPAR);
	*parlvl -= (token->type == CLOSEPAR);
	check_parenthesis(data, *parlvl, false);
	if (token->type == OPENPAR && !token->next)
		return (ft_error(data, "syntax error near unexpected token `('"),
			EXIT_FAILURE);
	if (token->type == OPENPAR && last != token
		&& (last->type == WORD || last->type == CMD))
	{
		ft_fprintf(STDERR_FILENO, "%s: syntax error near unexpected \
token `%s'\n", SHELL_NAME, token->next->str);
		data->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	else if (token->type == CLOSEPAR && token->next && !is_ope(token->next))
	{
		ft_fprintf(STDERR_FILENO, "%s: syntax error near unexpected \
token `%s'\n", SHELL_NAME, token->next->str);
		data->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static	int	check_redi(t_data *data, t_token *token)
{
	if (!token->next)
		return (ft_error(data, "syntax error near unexpected token `newline'"),
			EXIT_FAILURE);
	else if (token->next->type != WORD)
	{
		ft_fprintf(STDERR_FILENO, "%s: syntax error near unexpected token \
`%s'\n", SHELL_NAME, token->next->str);
		data->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	syntax_check(t_data *data, t_token *tokens)
{
	int		parlvl;
	t_token	*last;

	parlvl = 0;
	last = tokens;
	while (tokens)
	{
		if (is_ope(tokens))
		{
			if (check_ope(data, tokens) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (tokens->type == OPENPAR || tokens->type == CLOSEPAR)
		{
			if (check_par(data, tokens, last, &parlvl) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (STDOUT <= tokens->type && tokens->type <= STDIN_HEREDOC)
			if (check_redi(data, tokens) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		last = tokens;
		tokens = tokens->next;
	}
	return (check_parenthesis(data, parlvl, true));
}
