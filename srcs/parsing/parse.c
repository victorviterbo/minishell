/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:45:49 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/15 15:02:40 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_str(t_data *data, char *str, t_token_type type)
{
	char	*parsed;
	int		*isescaped;
	char	**parsed_arr;

	isescaped = is_quote_escaped(data, str);
	if (data->exit_status)
		return (NULL);	
	parsed = expand_var(data, str, isescaped);
	if (data->exit_status)
		return (NULL);
	free(isescaped);
	isescaped = is_quote_escaped(data, parsed);
	if (data->exit_status)
		return (NULL);
	remove_quotes(parsed, isescaped);
	parsed_arr = wildcard_handle(data, parsed, isescaped, type);
	free(isescaped);
	return (parsed_arr);
}

