/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:10:56 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 11:21:12 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	*is_quoted(char *str, char open_char, char close_char);
bool	*is_quote_escaped(char *str);
size_t	go_to_next(char *str, char *chars, size_t i);

bool	*is_quoted(char *str, char open_char, char close_char)
{
	bool	*isquoted;
	size_t	i;
	bool	between_quotes;

	i = 0;
	isquoted = ft_calloc(ft_strlen(str) + 1, sizeof(bool));
	if (!isquoted)
		return (NULL);
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

bool	*is_quote_escaped(char *str)
{
	bool	*escaped;
	size_t	i;
	bool	single_quoted;
	bool	double_quoted;

	escaped = ft_calloc(ft_strlen(str) + 1, sizeof(bool));
	if (!escaped)
		return (NULL);
	i = 0;
	single_quoted = false;
	double_quoted = false;
	while (str[i])
	{
		if (str[i] == '\'' && !double_quoted)
			single_quoted = !single_quoted;
		if (str[i] == '"' && !single_quoted)
			double_quoted = !double_quoted;
		escaped[i] = single_quoted;
		i++;
	}
	if (single_quoted || double_quoted)
		return (NULL);
	return (escaped);
}

size_t	go_to_next(char *str, char *chars, size_t i)
{
	bool	ws;

	ws = (ft_strchr(chars, ' ') != NULL);
	while (str[i] && ((ft_strchr(chars, str[i]) == NULL)
			&& !(ft_iswhitespace_eq(str[i]) && ws)))
		i++;
	return (i);
}
