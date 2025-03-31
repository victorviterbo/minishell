/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:45:49 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/01 00:16:31 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_str(t_data *data, char *str, bool inplace);

char	*parse_str(t_data *data, char *str, bool inplace)
{
	char	*parsed;
	int		*isescaped;

	isescaped = is_quote_escaped(data, str);
	if (data->exit_status)
		return (NULL);
	parsed = expand_var(data, str, isescaped);
	if (data->exit_status)
		return (NULL);
	if (isescaped)
		free(isescaped);
	isescaped = is_quote_escaped(data, parsed);
	if (data->exit_status)
		return (NULL);
	parsed = remove_quotes_ws(data, parsed, isescaped, true);
	if (data->exit_status)
		return (NULL);
	if (isescaped)
		free(isescaped);
	if (inplace)
		free(str);
	return (parsed);
}
