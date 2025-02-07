/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:10:56 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/07 15:08:21 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	*is_quoted(char *str, char open_char, char close_char);
size_t	go_to_next(char *cmd, char *chars, size_t i);

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

size_t	go_to_next(char *cmd, char *chars, size_t i)
{
	bool	ws;

	ws = (ft_strchr(chars, ' ') != NULL);
	while (cmd[i] && !(ft_strchr(chars, cmd[i])
			|| (ft_iswhitespace_eq(cmd[i]) && ws)))
		i++;
	return (i);
}
