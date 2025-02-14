/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:51:06 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 11:32:59 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(t_data *data, char *str);
char	*replace_var(t_data *data, char *str, size_t *i);

char	*expand_var(t_data *data, char *str)
{
	size_t	i;
	bool	*isquoted;
	char	*expanded;

	i = 0;
	expanded = ft_strdup(str);
	if (!expanded)
		ft_print_error("var expansion: memory allocation failed");
	isquoted = is_quote_escaped(expanded);
	if (!isquoted)
		ft_print_error("var expansion: unfinished quoting sequence");
	while (expanded[i])
	{
		if (expanded[i] == '$' && !isquoted[i])
			expanded = replace_var(data, expanded, &i);
		else
			i++;
	}
	free(isquoted);
	return (expanded);
}

char	*replace_var(t_data *data, char *str, size_t *i)
{
	char	*newstr;
	char	*varname;
	char	*varvalue;
	size_t	j;

	//TODO check for special replaces like $? and redirect accordingy
	if (str[*i + 1] == '{')
	{
		j = go_to_next(str, "}", *i + 2) + 1;
		varname = ft_substr(str, *i + 2, j - (*i + 3));
	}
	else
	{
		j = go_to_next(str, "\"\\\a\b\t\n\f\r $'", *i + 1);
		varname = ft_substr(str, *i + 1, j - (*i + 1));
	}
	varvalue = get_var(data, varname);
	free(varname);
	if (!varvalue)
		varvalue = ft_strdup("");
	newstr = ft_substr(str, 0, *i);
	*i += ft_strlen(varvalue);
	newstr = ft_strjoin_ip(newstr, varvalue, FREE_S1S2);
	newstr = ft_strjoin_ip(newstr, str + j, FREE_S1);
	free(str);
	return (newstr);
}
