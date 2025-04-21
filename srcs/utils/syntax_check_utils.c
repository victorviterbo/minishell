/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 02:07:40 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/21 12:55:21 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_ope(t_token *token)
{
	return (token->type == AND || token->type == OR || token->type == PIPE);
}

int	check_parenthesis(t_data *data, int parlvl, bool final_check)
{
	if (parlvl < 0)
		return (ft_error(data, "syntax error near unexpected token `)'"),
			EXIT_FAILURE);
	if (parlvl > 0 && final_check == TRUE)
		return (ft_error(data, "syntax error near unexpected token `('"),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_opening_par(t_data *data, t_token *token, t_token *last)
{
	if (!token->next)
		return (ft_error(data, "syntax error near unexpected token `('"),
			EXIT_FAILURE);
	if (last != token && (last->type == WORD || last->type == CMD))
	{
		ft_fprintf(STDERR_FILENO, "%s: syntax error near unexpected \
token `%s'\n", SHELL_NAME, token->next->str);
		data->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_closing_par(t_data *data, t_token *token, t_token *last)
{
	if (token->next && token->next->type == WORD)
	{
		ft_fprintf(STDERR_FILENO, "%s: syntax error near unexpected \
token `%s'\n", SHELL_NAME, token->next->str);
		data->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	if (token != last && last->type == OPENPAR)
		return (ft_error(data, " syntax error near unexpected token `)'"),
				EXIT_FAILURE);
	return (EXIT_SUCCESS);
}