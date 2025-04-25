/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:31:31 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/25 16:54:15 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_varname(t_data *data, char *str, int name_len)
{
	char	*varname;
	size_t	i;

	if (name_len == 0 || ft_isdigit(str[0]))
		return (ft_fprintf(STDERR_FILENO, "%s: export: %s: \
not a valid identifier\n", SHELL_NAME, str),
			data->exit_status = EXIT_FAILURE, NULL);
	varname = ft_substr(str, 0, name_len);
	if (!varname)
		return (ft_error(data, "variable parsing: memory allocation failed"),
			NULL);
	i = 0;
	while (varname[i])
	{
		if (ft_strchr(" +-{}/!@#$", varname[i]))
		{
			ft_fprintf(STDERR_FILENO, "%s: export: %s: not a valid identifier\n"
				SHELL_NAME, str);
			data->exit_status = EXIT_FAILURE;
			return (free(varname), NULL);
		}
		i++;
	}
	return (varname);
}
