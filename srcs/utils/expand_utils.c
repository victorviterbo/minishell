/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:03:51 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/27 19:02:56 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dry_run_allocate(t_data *data, char *str, int *isescaped)
{
	char	*new_str;
	size_t	new_size;
	size_t	j;

	j = 0;
	new_size = 0;
	while (str && str[j])
	{
		if (str[j] == '$' && need_expand(data, str, isescaped, j))
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
		ft_error(data, "variable substitution: memory allocation failed");
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
