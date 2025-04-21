/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 02:07:40 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/19 02:08:05 by vbronov          ###   ########.fr       */
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
	if (parlvl > 0 && final_check == FALSE)
		return (ft_error(data, "syntax error near unexpected token `('"),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
