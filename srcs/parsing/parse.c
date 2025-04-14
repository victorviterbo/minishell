/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:45:49 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/14 18:15:46 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**wildcard_handle(t_data *data, char *parsed, int *isescaped,
			t_token_type type);

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
	ft_printf("parsed_arr = %p, parsed = %p, parsed_arr[0] = %p\n", parsed_arr, parsed, parsed_arr[0]);
	return (parsed_arr);
}

char	**wildcard_handle(t_data *data, char *parsed, int *isescaped,
			t_token_type type)
{
	char	**parsed_arr;

	parsed_arr = NULL;
	if ((type == STDIN || type == WORD) && ft_strchr(parsed, '*'))
	{
		parsed_arr = substitute_wildcard(data, parsed, isescaped);
		if (data->exit_status == EXIT_FAILURE)
			free(parsed);
	}
	if (!parsed_arr && data->exit_status == EXIT_SUCCESS)
	{
		parsed_arr = ft_str_to_arr(parsed);
		if (!parsed_arr)
			return (ft_error(data, "parsing: memory allocation failed"),
				free(parsed), NULL);
	}
	return (parsed_arr);
}
