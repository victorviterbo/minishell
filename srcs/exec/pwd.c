/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:22:20 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/15 17:21:35 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data);
char	*ft_get_current_path(t_data *data);

void	ft_pwd(t_data *data)
{
	char	*current_path;
	size_t	printed;

	current_path = ft_get_current_path(data);
	if (data->exit_status)
		return ;
	printed = ft_printf("%s\n", current_path);
	if (printed != ft_strlen(current_path) + 1)
	{
		free(current_path);
		return (ft_error(data, "pwd: could not display path"));
	}
	free(current_path);
	return ;
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
		return (ft_error(data, "pwd: could not load path"), NULL);
	else if (retvalue != current_path)
		return (ft_error(data, "pwd: an unknown error has occured"), NULL);
	return (current_path);
}
