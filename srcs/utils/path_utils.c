/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:24:23 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/24 16:25:16 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isdirectory(char *path)
{
	DIR	*directory;

	directory = opendir(path);
	if (directory == NULL)
	{
		closedir(directory);
		return (false);
	}
	else
	{
		closedir(directory);
		return (true);
	}
}
