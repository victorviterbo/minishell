/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:10:56 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/01 00:20:58 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		*is_quote_escaped(t_data *data, char *str);
char	*remove_quotes_ws(t_data *data, char *str, int *isescaped,
			bool inplace);
size_t	go_to_next(char *str, char *chars, size_t i);

int	*is_quote_escaped(t_data *data, char *str)
{
	int		*escaped;
	int		quotation;

	if (!str)
		return (ft_error(data, "parsing: invalid input string"), NULL);
	escaped = ft_calloc(ft_strlen(str) + 1, sizeof(int));
	if (!escaped)
		return (ft_error(data, "parsing: memory allocation failed"), NULL);
	quotation = IS_NOT_QUOTED;
	while (*str)
	{
		if (*str == '\'' && quotation != IS_DOUBLE_QUOTED)
			quotation = IS_NOT_QUOTED;
		if (*str == '"' && quotation != IS_SINGLE_QUOTED)
			quotation = IS_NOT_QUOTED;
		*escaped = quotation;
		str++;
		escaped++; // TODO: we cannot use escaped++ here, because we need to free the pointer
	}
	if (quotation != IS_NOT_QUOTED)
		return (free(escaped), ft_error(data,
				"parsing: unfinished quoting sequence"), NULL);
	return (escaped);
}

char	*remove_quotes_ws(t_data *data, char *str, int *isescaped, bool inplace)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	newstr = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!newstr)
		return (ft_error(data, "parsing: memory allocation failed"), NULL);
	i = -1;
	j = -1;
	while (str[i + 1])
	{
		i++;
		if ((str[i] == '\'' && isescaped[i] != IS_DOUBLE_QUOTED)
			|| (str[i] == '"' && isescaped[i] != IS_SINGLE_QUOTED)
			|| (str[i] == ' ' && str[i + 1] == ' '
				&& isescaped[i] == IS_NOT_QUOTED))
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
			&& !(ft_isspace(str[i]) && ws)))
		i++;
	return (i);
}
