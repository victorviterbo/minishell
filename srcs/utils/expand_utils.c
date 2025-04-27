/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:03:51 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/27 16:49:24 by vviterbo         ###   ########.fr       */
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
	while (str[j])
	{
		if (str[j] == '$' && need_expand(data, str, isescaped, j))
		{
			dry_run_skip_var(data, str, &new_size, &j);
			if (data->exit_status)
				return (NULL);
			j += 2;
		}
		else
		{
			new_size++;
			j++;
		}
	}
	new_str = ft_calloc(new_size + 1, sizeof(char));
	if (!new_str)
		return (ft_error(data, "variable substitution: memory "
				"allocation failed"), NULL);
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
