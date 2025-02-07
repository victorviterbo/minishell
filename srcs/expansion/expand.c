/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:51:06 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/07 15:25:11 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		expand_var(t_data *data, char *str);
char	*replace_var(t_data *data, char *str, size_t i, bool inplace);

int	expand_var(t_data *data, char *str)
{
	char	*expanded;
	size_t	i;
	bool	*isquoted;

	i = 0;
	isquoted = is_quoted(str, '\'', '\'');
	if (!isquoted)
		ft_print_error("var expansion: unfinished quoting sequence");
	expanded = ft_strdup(str);
	if (!expanded)
		ft_print_error("var expansion: memory allocation failed");
	while (str[i])
	{
		if (str[i] == '$' && !isquoted[i])
			expanded = replace_var(data, expanded, i, true);
		i++;
	}
}

char	*replace_var(t_data *data, char *str, size_t i, bool inplace)
{
	char	*newstr;
	char	*varname;
	char	*varvalue;
	bool	*isquoted;
	size_t	j;

	if (str[i + 1] == '{')
	{
		j = go_to_next(str, "}", i);
		i += 1;
	}
	else
	{
		j = go_to_next(str, i, ' ', );
		varname = ft_substr(str, i, j - i); go_to_next(str, i, ' ', false);
	}
	varvalue = get_var(data, varname);
	free(varname);
	if (!varvalue)
		varvalue = ft_strdup("");
	newstr = ft_substr(str, 0, i);
	new_str = ft_strjoin_ip(newstr, varvalue)
}
