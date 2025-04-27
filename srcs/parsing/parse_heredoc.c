/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:51:06 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/27 20:13:23 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var_hd(t_data *data, char *str, int *isescaped)
{
	size_t	i;
	size_t	j;
	char	*expanded;

	expanded = dry_run_allocate_hd(data, str, isescaped);
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	while (str[j] && data->exit_status == EXIT_SUCCESS)
	{
		if (str[j] == '$' && need_expand(data, str, isescaped, j))
		{
			if (replace_var(data, str, expanded, &j) != EXIT_SUCCESS)
				return (free(expanded), NULL);
			i = ft_strlen(expanded);
		}
		else if (data->exit_status == EXIT_SUCCESS)
		{
			expanded[i] = str[j];
			i++;
			j++;
		}
	}
	return (expanded);
}

char	*dry_run_allocate_hd(t_data *data, char *str, int *isescaped)
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
