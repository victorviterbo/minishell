/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:03:51 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/27 21:29:19 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dry_run_allocate(t_data *data, char *str, t_quotes *quotes)
{
	char	*tmp;
	size_t	new_size;
	size_t	j;

	j = 0;
	new_size = 0;
	while (str && str[j])
	{
		if (str[j] == '$' && need_expand(data, str, quotes->old, j))
			dry_run_skip_var(data, str, &new_size, &j);
		else
		{
			new_size++;
			j++;
		}
		if (data->exit_status)
			return (NULL);
	}
	tmp = ft_calloc(new_size + 1, sizeof(char));
	if (!tmp)
		return (ft_error(data, "memory allocation failed"), NULL);
	quotes->new = ft_calloc(new_size + 1, sizeof(int));
	if (!quotes)
		return (ft_error(data, "memory allocation failed"), free(tmp), NULL);
	return (tmp);
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
