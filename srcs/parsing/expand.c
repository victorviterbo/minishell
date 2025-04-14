/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:51:06 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/14 22:48:33 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(t_data *data, char *str, int *isescaped)
{
	size_t	i;
	size_t	j;
	char	*expanded;

	expanded = dry_run_allocate(data, str, isescaped);
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	while (str[j] && data->exit_status == EXIT_SUCCESS)
	{
		if (str[j] == '$' && isescaped[j] != IS_SINGLE_QUOTED)
		{
			if (replace_var(data, str, expanded, &j) != EXIT_SUCCESS)
				return (free(expanded), NULL);
			i = ft_strlen(expanded);
		}
		else
		{
			expanded[i] = str[j];
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
	if (data->exit_status)
		return (data->exit_status);
	varvalue = get_var(data, varname);
	free(varname);
	if (data->exit_status)
		return (free(str), data->exit_status);
	if (!varvalue && data->exit_status == EXIT_SUCCESS)
		varvalue = ft_strdup("");
	if (!varvalue)
		return (ft_error(data, "variable substitution: memory allocation \
failed"), free(varname), EXIT_FAILURE);
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
	else
	{
		*j = go_to_next(str, "\"\\\n $'", i + 1);
		varname = ft_substr(str, i + 1, *j - (i + 1));
	}
	if (!varname)
		return (ft_error(data, "variable substitution: memory \
allocation failed"), NULL);
	return (varname);
}

char	*dry_run_allocate(t_data *data, char *str, int *isescaped)
{
	char	*new_str;
	size_t	new_size;
	size_t	j;

	j = 0;
	new_size = 0;
	while (str[j])
	{
		if (str[j] == '$' && isescaped[j] != IS_SINGLE_QUOTED)
		{
			dry_run_skip_var(data, str, &new_size, &j);
			if (data->exit_status)
				return (NULL);
		}
		else
		{
			new_size++;
			j++;
		}
	}
	new_str = ft_calloc(new_size + 1, sizeof(char));
	if (!new_str)
		return (ft_error(data, "variable substitution: memory \
allocation failed"), NULL);
	return (new_str);
}

void	dry_run_skip_var(t_data *data, char *str, size_t *new_size, size_t *j)
{
	char	*varname;
	char	*varvalue;

	varname = parse_varname(data, str, j);
	if (!varname)
		return ;
	varvalue = get_var(data, varname);
	if (!varvalue)
		return (free(varname));
	*new_size += ft_strlen(varvalue);
	free(varname);
	free(varvalue);
	return ;
}
