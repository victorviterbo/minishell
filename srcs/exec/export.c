/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:08:58 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/26 20:15:39 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char *args[], t_data *data);

int	ft_export(char *args[], t_data *data)
{
	int		i;
	int		success;

	i = 0;
	success = 0;
	while (args[i])
	{
		success += new_var(data->envp, args[i]);
		i++;
	}
	return (success);
}
