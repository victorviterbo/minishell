/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:45:49 by vviterbo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/14 11:38:06 by vviterbo         ###   ########.fr       */
=======
/*   Updated: 2025/02/14 11:58:04 by vviterbo         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_str(t_data *data, char *str);

char	*parse_str(t_data *data, char *str)
{
	char	*parsed;
	char	*tmp;
	bool	*isquoted;

	isquoted = is_quoted(str, '\'', '\'');
	if (!isquoted)
		ft_print_error("parsing: unfinished quoting sequence");
	free(isquoted);
	isquoted = is_quoted(str, '{', '}');
	if (!isquoted)
		ft_print_error("parsing: unfinished quoting sequence");
	free(isquoted);
	isquoted = is_quoted(str, '"', '"');
	if (!isquoted)
		ft_print_error("parsing: unfinished quoting sequence");
	free(isquoted);
	//parsed = ft_str_replace(str, "\"", "");
	//if (!parsed)
	//	ft_print_error("parsing: memory allocation failed");
	parsed = expand_var(data, str);
	if (!parsed)
		ft_print_error("parsing: variable expansion failed");
	tmp = ft_str_replace(parsed, "'", "");
	free(parsed);
	parsed = tmp;
	if (!parsed)
		ft_print_error("parsing: memory allocation failed");
	return (parsed);
}
