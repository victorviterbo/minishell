/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:22:20 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/17 22:46:14 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pwd(void);

char	*ft_pwd(void)
{
	char	*current_path;
	int		attempts;
	int		retvalue;

	attempts = 1;
	current_path = ft_calloc(PATH_MAX + 1, sizeof(char));
	retvalue = getcwd(current_path, PATH_MAX * attempts);
	while (attempts < 3 && retvalue == ERANGE)
	{
		free(current_path);
		current_path = ft_calloc(PATH_MAX * attempts + 1, sizeof(char));
		retvalue = getcwd(current_path, PATH_MAX * attempts);
	}
	if (retvalue == ERANGE || retvalue == EACCES || retvalue == EINVAL)
		ft_perror_exit("Minishell: pwd");
	else if (retvalue != current_path)
		ft_custom_error_exit("Minishell: pwd: an unknown error has occured");
	else
		return (current_path);
}
