/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:45:49 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:22:20 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_str(t_data *data, char *str);

char	*parse_str(t_data *data, char *str)
{
	char	*parsed;
	int		*isescaped;

	isescaped = is_quote_escaped(str);
	if (!isescaped)
		ft_print_error("parsing: unfinished quotation");
	parsed = expand_var(data, str, isescaped);
	if (!parsed)
		ft_print_error("parsing: variable expansion failed");
	free(isescaped);
	isescaped = is_quote_escaped(parsed);
	if (!isescaped)
		ft_print_error("parsing: unfinished quotation");
	parsed = remove_quotes_ws(parsed, isescaped, true);
	if (!parsed)
		ft_print_error("parsing: removing of quotations failed");
	free(isescaped);
	return (parsed);
}
