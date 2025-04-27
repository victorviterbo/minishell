/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:45:49 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/27 20:28:11 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_quotes(t_quotes *quotes)
{
	if (!quotes)
		return ;
	if (quotes->old)
		free(quotes->old);
	if (quotes->new)
		free(quotes->new);
	free(quotes);
}

/**
 * @brief Parses a string according to the specified token type
 *
 * This function parses the input string based on the token type provided
 * and stores relevant information in the data structure.
 * It handles variable expansion, wildcard handling, and quote removal.
 *
 * @param data Pointer to the shell's data structure
 * @param str String to be parsed
 * @param type Type of token to guide the parsing process
 *
 * @return Array of strings resulting from the parsing process, or NULL on error
 */
char	**parse_str(t_data *data, char *str, t_token_type type)
{
	char		*parsed;
	char		**parsed_arr;
	t_quotes	*quotes;

	quotes = ft_calloc(1, sizeof(t_quotes));
	if (!quotes)
		return (ft_error(data, "variable expansion: memory allocation failed"),
			NULL);
	quotes->old = parse_quote_positions(data, str);
	if (!quotes->old)
		return (free(quotes), NULL);
	parsed = expand_var(data, str, quotes);
	if (!parsed)
		return (free_quotes(quotes), NULL);
	remove_quotes(parsed, quotes->new);
	parsed_arr = wildcard_handle(data, parsed, quotes->new, type);
	free_quotes(quotes);
	return (parsed_arr);
}
