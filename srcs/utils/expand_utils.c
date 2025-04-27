/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:03:51 by vviterbo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/27 19:07:16 by vviterbo         ###   ########.fr       */
=======
/*   Updated: 2025/04/27 19:02:56 by vbronov          ###   ########.fr       */
>>>>>>> ddeed62223f51692da8e6e51a0d47ec0ea508560
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dry_run_allocate(t_data *data, char *str, t_quotes *quotes)
{
	char	*new_str;
	size_t	new_size;
	size_t	j;

	j = 0;
	new_size = 0;
	while (str && str[j])
	{
		if (str[j] == '$' && need_expand(data, str, quotes->old, j))
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
	quotes->new = ft_calloc(new_size + 1, sizeof(int));
	if (!quotes)
		return (ft_error(data, "variable substitution: memory allocation\
 failed"), free(new_str), NULL);
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
