/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkashi <tkashi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:22:20 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/24 04:38:24 by tkashi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data, char **args, int argc)
{
	char	*current_path;
	size_t	printed;

	(void)args;
	if (argc > 1)
		return (ft_error(data, "pwd: too many arguments"),EXIT_FAILURE);
	current_path = ft_get_current_path(data);
	if (!current_path)
	{
		data->exit_status = EXIT_SUCCESS;
		current_path = get_var(data, "PWD");
		if (!current_path)
			return (ft_error(data, "pwd: PWD not set"),
				data->exit_status = EXIT_FAILURE, EXIT_FAILURE);
	}
	printed = ft_printf("%s\n", current_path);
	if (printed != ft_strlen(current_path) + 1)
	{
		free(current_path);
		ft_error(data, "pwd: could not display path");
		return (EXIT_FAILURE);
	}
	free(current_path);
	return (EXIT_SUCCESS);
}

char	*ft_get_current_path(t_data *data)
{
	char	*current_path;
	int		attempt;
	char	*retvalue;

	retvalue = NULL;
	attempt = 1;
	while ((attempt <= 2 && data->exit_status == ERANGE) || attempt == 1)
	{
		current_path = ft_calloc(PATH_MAX * attempt + 1, sizeof(char));
		if (!current_path)
			return (data->exit_status = errno, NULL);
		retvalue = getcwd(current_path, PATH_MAX * attempt);
		data->exit_status = errno;
		if (!retvalue)
			free(current_path);
		attempt++;
	}
	return (retvalue);
}
