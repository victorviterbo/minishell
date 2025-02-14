/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:10:56 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:20:29 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	*is_quoted(char *str, char open_char, char close_char);
int		*is_quote_escaped(char *str);
char	*remove_quotes_ws(char *str, int *isescaped, bool inplace);
size_t	go_to_next(char *str, char *chars, size_t i);

bool	*is_quoted(char *str, char open_char, char close_char)
{
	bool	*isquoted;
	size_t	i;
	bool	between_quotes;

	i = 0;
	isquoted = ft_calloc(ft_strlen(str) + 1, sizeof(bool));
	if (!isquoted)
		ft_print_error("parsing: memory allocation failed");
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

int	*is_quote_escaped(char *str)
{
	int		*escaped;
	size_t	i;
	bool	single_quoted;
	bool	double_quoted;

	escaped = ft_calloc(ft_strlen(str) + 1, sizeof(int));
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
		if (single_quoted && double_quoted)
			ft_print_error("Quote parsing failed !");
		escaped[i] = single_quoted * IS_SINGLE_QUOTED
			+ double_quoted * IS_DOUBLE_QUOTED;
		i++;
	}
	if (single_quoted || double_quoted)
		return (free(escaped), NULL);
	return (escaped);
}

char	*remove_quotes_ws(char *str, int *isescaped, bool inplace)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	newstr = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!newstr)
		ft_print_error("parsing: memory allocation failed");
	i = -1;
	j = -1;
	while (str[i + 1])
	{
		i++;
		if ((str[i] == '\'' && isescaped[i] != IS_DOUBLE_QUOTED)
			|| (str[i] == '"' && isescaped[i] != IS_SINGLE_QUOTED)
			|| (str[i] == ' ' && str[i + 1] == ' '
				&& isescaped[i] != IS_DOUBLE_QUOTED))
			continue ;
		j++;
		newstr[j] = str[i];
	}
	newstr[j + 1] = '\0';
	if (inplace)
		free(str);
	return (newstr);
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
