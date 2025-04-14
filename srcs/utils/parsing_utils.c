/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:10:56 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/14 16:13:10 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*is_quote_escaped(t_data *data, char *str)
{
	int		*escaped;
	int		quotation;
	size_t	i;

	if (!str)
		return (ft_error(data, "parsing: invalid input string"), NULL);
	escaped = ft_calloc(ft_strlen(str) + 1, sizeof(int));
	if (!escaped)
		return (ft_error(data, "parsing: memory allocation failed"), NULL);
	quotation = IS_NOT_QUOTED;
	i = 0;
	while (*str)
	{
		if (*str == '\'' && quotation != IS_DOUBLE_QUOTED)
			quotation = IS_SINGLE_QUOTED * (!quotation);
		if (*str == '"' && quotation != IS_SINGLE_QUOTED)
			quotation = IS_DOUBLE_QUOTED * (!quotation);
		escaped[i] = quotation;
		str++;
		i++;
	}
	if (quotation != IS_NOT_QUOTED)
		return (free(escaped), ft_error(data,
				"parsing: unfinished quoting sequence"), NULL);
	return (escaped);
}

void	remove_quotes(char *str, int *isescaped)
{
	size_t	i;
	size_t	offset;

	i = 0;
	offset = 0;
	while (str[i + offset])
	{
		if ((str[i + offset] == '\''
				&& isescaped[i + offset] != IS_DOUBLE_QUOTED)
			|| (str[i + offset] == '"'
				&& isescaped[i + offset] != IS_SINGLE_QUOTED))
			offset++;
		else
		{
			str[i] = str[i + offset];
			isescaped[i] = isescaped[i + offset];
			i++;
		}
	}
	str[i] = '\0';
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
