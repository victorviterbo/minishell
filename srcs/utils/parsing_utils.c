/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:10:56 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/07 14:27:09 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	*is_quoted(char *str, char open_char, char close_char);
size_t	go_to_next(char *cmd, size_t i, char c, bool esc);

bool	*is_quoted(char *str, char open_char, char close_char)
{
	bool	*isquoted;
	size_t	i;
	bool	between_quotes;

	i = 0;
	isquoted = ft_calloc(ft_strlen(str) + 1, sizeof(bool));
	between_quotes = false;
	while (str[i])
	{
		if (str[i] == open_char && !between_quotes)
			between_quotes = !between_quotes;
		else if (str[i] == close_char && between_quotes)
			between_quotes = !between_quotes;
		isquoted[i] = between_quotes;
		i++;
	}
	if (between_quotes)
		return (free(isquoted), NULL);
	return (isquoted);
}

size_t	go_to_next(char *cmd, size_t i, char c, bool esc)
{
	if (c == '(')
		c = ')';
	if (c == '{')
		c = '}';
	if (c != ' ')
		while (cmd[i] && cmd[i] != c && (!i || cmd[i - 1] != '\\' || !esc))
			i++;
	else
		while (cmd[i] && !ft_iswhitespace_eq(cmd[i])
			&& (!i || cmd[i - 1] != '\\' || !esc))
			i++;
	if (!cmd[i])
		ft_print_error("var expansion: unfinished experession");
	return (i);
}
