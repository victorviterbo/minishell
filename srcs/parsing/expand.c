/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:51:06 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/27 19:11:26 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(t_data *data, char *str, t_quotes *quotes)
{
	size_t	i;
	size_t	j;
	char	*expanded;

	expanded = dry_run_allocate(data, str, quotes);
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	while (str[j] && data->exit_status == EXIT_SUCCESS)
	{
		if (str[j] == '$' && need_expand(data, str, quotes->old, j))
		{
			if (replace_var(data, str, expanded, &j) != EXIT_SUCCESS)
				return (free(expanded), NULL);
			i = ft_strlen(expanded);
		}
		else if (data->exit_status == EXIT_SUCCESS)
		{
			expanded[i] = str[j];
			quotes->new[i] = quotes->old[j];
			i++;
			j++;
		}
	}
	return (expanded);
}

int	replace_var(t_data *data, char *str, char *expanded, size_t *j)
{
	char	*varvalue;
	char	*varname;

	varname = parse_varname(data, str, j);
	if (!varname)
		return (data->exit_status);
	varvalue = get_var(data, varname);
	free(varname);
	if (data->exit_status)
		return (data->exit_status);
	if (!varvalue && data->exit_status == EXIT_SUCCESS)
		varvalue = ft_strdup("");
	if (!varvalue)
		return (ft_error(data, "variable substitution: memory allocation\
 failed"), EXIT_FAILURE);
	ft_strlcat(expanded, varvalue,
		ft_strlen(expanded) + ft_strlen(varvalue) + 1);
	free(varvalue);
	return (EXIT_SUCCESS);
}

char	*parse_varname(t_data *data, char *str, size_t *j)
{
	char	*varname;
	int		i;

	i = *j;
	if (str[i + 1] == '{')
	{
		*j = go_to_next(str, "}", i + 2) + 1;
		varname = ft_substr(str, i + 2, *j - (i + 3));
	}
	else if (str[i + 1] != '?')
	{
		*j = go_to_next(str, "\"\\\n $'.{}+-*/=", i + 1);
		varname = ft_substr(str, i + 1, *j - (i + 1));
	}
	else
	{
		*j += 2;
		varname = ft_strdup("?");
	}
	if (!varname)
		return (ft_error(data,
				"variable substitution: memory allocation failed"), NULL);
	return (varname);
}

bool	need_expand(t_data *data, char *str, int *isescaped, int j)
{
	if (isescaped[j] == IS_SINGLE_QUOTED)
		return (false);
	if (str[j + 1] == '{' && !ft_strchr(str, '}'))
		return (ft_error(data, "${: bad substitution"), false);
	if (!ft_strncmp(str + j, "${}", 3))
		return (ft_error(data, "${}: bad substitution"), false);
	if (ft_strncmp(str + j, "${?", 3) != ft_strncmp(str + j, "${?}", 4))
	{
		*(ft_strchr(str + j, '}') + 1) = '\0';
		ft_fprintf(STDERR_FILENO, "%s: %s: bad substitution",
			SHELL_NAME, str + j);
		return (data->exit_status = EXIT_FAILURE, false);
	}
	else if (isescaped[j] == IS_DOUBLE_QUOTED && str[j + 1] == '"')
		return (false);
	else if (ft_strchr("\\\n $.}", str[j + 1]))
		return (false);
	return (true);
}
