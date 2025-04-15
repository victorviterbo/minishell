/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:10:43 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/15 17:41:27 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_ope(t_token *token)
{
	if (token->type == AND || token->type == OR || token->type == PIPE)
		return (true);
	return (false);
}

static	int	check_ope(t_data *data, t_token *token)
{
	if (!token->next)
		return (ft_error(data, "syntax error near unexpected token `newline'"),
			EXIT_FAILURE);
	else if (is_ope(token->next))
	{
		ft_fprintf(STDERR_FILENO, "syntax error near unexpected token `%s'\n", \
			token->next->str);
		data->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static	int	check_par(t_data *data, t_token *token, int *parlvl)
{
	*parlvl += (token->type == OPENPAR);
	*parlvl -= (token->type == CLOSEPAR);
	if (*parlvl < 0)
		return (ft_error(data, "syntax error near unexpected token `)'"),
			EXIT_FAILURE);
	if (token->type == OPENPAR && !token->next)
		return (ft_error(data, "syntax error near unexpected token `('"),
			EXIT_FAILURE);
	else if (token->type == CLOSEPAR && token->next && !is_ope(token->next))
	{
		ft_fprintf(STDERR_FILENO, "syntax error near unexpected token `%s'\n", \
			token->next->str);
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
	else if (!token->next->type == WORD)
	{
		ft_fprintf(STDERR_FILENO, "syntax error near unexpected token `%s'\n", \
			token->next->str);
		data->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	syntax_check(t_data *data, t_token *tokens)
{
	int	parlvl;

	parlvl = 0;
	while (tokens)
	{
		if (is_ope(tokens))
		{
			if (check_ope(data, tokens) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (tokens->type == OPENPAR || tokens->type == CLOSEPAR)
		{
			if (check_par(data, tokens, &parlvl) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (STDIN <= tokens->type && tokens->type <= STDIN_HEREDOC)
			if (check_redi(data, tokens) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		tokens = tokens->next;
	}
	if (parlvl)
		return (ft_error(data, "syntax error near unexpected token `('"),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
