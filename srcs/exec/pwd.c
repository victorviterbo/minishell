/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:22:20 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/30 23:44:37 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data, char **args, int argc)
{
	char	*current_path;
	size_t	printed;

	if (argc > 1)
	{
		ft_error(data, "pwd: too many arguments");
		return (EXIT_FAILURE);
	}
	(void)args;
	current_path = ft_get_current_path(data);
	if (data->exit_status)
		return (EXIT_FAILURE);
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
	int		attempts;
	char	*retvalue;

	attempts = 1;
	current_path = ft_calloc(PATH_MAX + 1, sizeof(char));
	if (!current_path)
		return (ft_error(data, "pwd: memory allocation failed"), NULL);
	retvalue = getcwd(current_path, PATH_MAX * attempts);
	while (attempts < 3 && retvalue == NULL && errno == ERANGE)
	{
		attempts++;
		free(current_path);
		current_path = ft_calloc(PATH_MAX * attempts + 1, sizeof(char));
		if (!current_path)
			return (ft_error(data, "pwd: memory allocation failed"), NULL);
		retvalue = getcwd(current_path, PATH_MAX * attempts);
	}
	if (retvalue == NULL)
		return (free(current_path),
			ft_error(data, "pwd: could not load path"), NULL);
	return (current_path);
}
