/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:02:31 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/19 21:44:22 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*node_type_to_string_expand(enum e_token_type type)
{
	if (type == AND)
		return ("AND");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == OPENPAR)
		return ("OPENPAR");
	else if (type == CLOSEPAR)
		return ("CLOSEPAR");
	else if (type == CMD)
		return ("CMD");
	else
		return ("UNKNOWN");
}

const char	*node_type_to_string(enum e_token_type type)
{
	if (type == WORD)
		return ("WORD");
	else if (type == STDIN)
		return ("STDIN");
	else if (type == STDIN_HEREDOC)
		return ("STDIN_HEREDOC");
	else if (type == STDOUT)
		return ("STDOUT");
	else if (type == STDOUT_APPEND)
		return ("STDOUT_APPEND");
	else if (type == OR)
		return ("OR");
	else
		return (node_type_to_string_expand(type));
}
