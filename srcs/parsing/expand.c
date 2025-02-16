/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:51:06 by vviterbo          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/02/14 16:50:53 by vviterbo         ###   ########.fr       */
=======
/*   Updated: 2025/02/16 17:06:48 by vviterbo         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(t_data *data, char *str, int *isescaped);
char	*replace_var(t_data *data, char *str, size_t *i, size_t *j);

char	*expand_var(t_data *data, char *str, int *isescaped)
{
	size_t	i;
	size_t	j;
	char	*expanded;

	i = 0;
	j = 0;
	expanded = ft_strdup(str);
	if (!expanded)
		ft_print_error("var expansion: memory allocation failed");
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
	char	*varname;
	char	*varvalue;

	//TODO check for special replaces like $? and redirect accordingy
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
	varvalue = get_var(data, varname);
	free(varname);
	if (!varvalue)
		varvalue = ft_strdup("");
	newstr = ft_substr(str, 0, *i);
	*i += ft_strlen(varvalue);
	newstr = ft_strjoin_ip(newstr, varvalue, FREE_S1S2);
	newstr = ft_strjoin_ip(newstr, str + *j, FREE_S1);
	free(str);
	return (newstr);
}
