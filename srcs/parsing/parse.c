/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:45:49 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/24 17:53:52 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*parsed;
	int		*isescaped;
	char	**parsed_arr;

	isescaped = parse_quote_positions(data, str);
	if (!isescaped)
		return (NULL);
	parsed = expand_var(data, str, isescaped);
	free(isescaped);
	if (!parsed)
		return (NULL);
	isescaped = parse_quote_positions(data, parsed);
	if (!isescaped)
		return (free(parsed), NULL);
	remove_quotes(parsed, isescaped);
	parsed_arr = wildcard_handle(data, parsed, isescaped, type);
	free(isescaped);
	return (parsed_arr);
}
