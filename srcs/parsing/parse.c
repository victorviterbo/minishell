/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:45:49 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/10 21:59:19 by vviterbo         ###   ########.fr       */
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
	parsed = remove_quotes_ws(data, parsed, isescaped, true); //TODO investigate
	if (data->exit_status)
		return (NULL);
	if (isescaped)
		free(isescaped);
	if (inplace)
		free(str);
	//TODO: refactor and include wildcard treatment
	return (parsed);
}
// TODO
// 	1. quote
//	2. variable
//	3. wildcards