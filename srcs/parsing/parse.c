/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:45:49 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/18 17:45:26 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_str(t_data *data, char *str, t_token_type type)
{
	char	*parsed;
	int		*isescaped;
	char	**parsed_arr;

	isescaped = is_quote_escaped(data, str);
	if (!isescaped)
		return (NULL);
	parsed = expand_var(data, str, isescaped);
	free(isescaped);
	if (!parsed)
		return (NULL);
	isescaped = is_quote_escaped(data, parsed);
	if (!isescaped)
		return (free(parsed), NULL);
	remove_quotes(parsed, isescaped);
	parsed_arr = wildcard_handle(data, parsed, isescaped, type);
	free(parsed);
	free(isescaped);
	return (parsed_arr);
}
