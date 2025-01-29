/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:22:20 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/29 10:42:41 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(void);
char	*ft_getpath(void);

int	ft_pwd(void)
{
	char	*current_path;
	size_t	printed;

	current_path = ft_get_current_path();
	printed = ft_printf("%s\n", current_path);
	if (printed != ft_strlen(current_path) + 1)
	{
		free(current_path);
		return (EXIT_FAILURE);
	}
	free(current_path);
	return (EXIT_SUCCESS);
}

char	*ft_get_current_path(void)
{
	char	*current_path;
	int		attempts;
	char	*retvalue;

	attempts = 1;
	current_path = ft_calloc(PATH_MAX + 1, sizeof(char));
	if (!current_path)
		ft_custom_error_exit("Minishell: pwd: memory allocation failed");
	retvalue = getcwd(current_path, PATH_MAX * attempts);
	while (attempts < 3 && retvalue == NULL && errno == ERANGE)
	{
		attempts++;
		free(current_path);
		current_path = ft_calloc(PATH_MAX * attempts + 1, sizeof(char));
		if (!current_path)
			ft_custom_error_exit("Minishell: pwd: memory allocation failed");
		retvalue = getcwd(current_path, PATH_MAX * attempts);
	}
	if (retvalue == NULL)
		ft_perror_exit("Minishell: pwd");
	else if (retvalue != current_path)
		ft_custom_error_exit("Minishell: pwd: an unknown error has occured");
	return (current_path);
}
