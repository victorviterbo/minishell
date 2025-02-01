/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:10:56 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/01 12:46:49 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	*is_quoted(char *str, char open_char, char close_char);

bool	*is_quoted(char *str, char open_char, char close_char)
{
	bool	*isquoted;
	size_t	i;
	bool	between_quotes;

	i = 0;
	isquoted = ft_calloc(ft_strlen(str), sizeof(bool));
	between_quotes = false;
	while (str[i])
	{
		if (str[i] == open_char && !between_quotes)
			between_quotes = !between_quotes;
		else if (str[i] == close_char && between_quotes)
			between_quotes = !between_quotes;
		isquoted[i] = between_quotes;
		//ft_printf("%c and %c vs %c, %i\n", open_char, close_char, str[i], str[i] == open_char);
		//ft_printf("assigning %i to %i\n", between_quotes, isquoted[i]);
		i++;
	}
	if (between_quotes)
		return (free(isquoted), NULL);
	return (isquoted);
}

