/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:51:06 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/15 16:36:32 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(t_data *data, char *str, int *isescaped);
char	*replace_var(t_data *data, char *str, size_t *i, size_t *j);
char	*get_varname(t_data *data, char *str, size_t *i, size_t *j);

char	*expand_var(t_data *data, char *str, int *isescaped)
{
	size_t	i;
	size_t	j;
	char	*expanded;

	i = 0;
	j = 0;
	expanded = ft_strdup(str);
	if (!expanded)
		return (ft_error(data, "var expansion: memory allocation failed"),
			NULL);
	while (expanded[i] && str[j])
	{
		if (expanded[i] == '$' && isescaped[j] != IS_SINGLE_QUOTED)
			expanded = replace_var(data, expanded, &i, &j);
		else
		{
			i++;
			j++;
		}
	}
	return (expanded);
}

char	*replace_var(t_data *data, char *str, size_t *i, size_t *j)
{
	char	*newstr;
	char	*varvalue;
	char	*varname;

	varname = get_varname(data, str, i, j);
	if (data->exit_status)
		return (NULL);
	varvalue = get_var(data, varname);
	free(varname);
	if (data->exit_status)
		return (free(str), NULL);
	if (!varvalue)
		varvalue = ft_strdup("");
	if (!varvalue)
		return (free(str), ft_error(data, "variable substitution: memory \
allocation failed"), NULL);
	newstr = ft_substr(str, 0, *i);
	newstr = ft_strjoin_ip(newstr, varvalue, FREE_S1S2);
	newstr = ft_strjoin_ip(newstr, str + *j, FREE_S1);
	if (!newstr)
		return (free(str), ft_error(data, "variable substitution: memory \
allocation failed"), NULL);
	*i += ft_strlen(varvalue);
	free(str);
	return (newstr);
}

char	*get_varname(t_data *data, char *str, size_t *i, size_t *j)
{
	char	*varname;

	if (str[*i + 1] == '{')
	{
		*j = go_to_next(str, "}", *i + 2) + 1;
		varname = ft_substr(str, *i + 2, *j - (*i + 3));
	}
	else
	{
		*j = go_to_next(str, "\"\\\n $'", *i + 1);
		varname = ft_substr(str, *i + 1, *j - (*i + 1));
	}
	if (!varname)
		return (ft_error(data, "variable substitution: memory \
allocation failed"), NULL);
	return (varname);
}
