/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:08:58 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/28 22:45:40 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_data *data, char *args[]);

int	ft_export(t_data *data, char *args[])
{
	int		i;
	int		success;

	if (!data || !data->envp || !args)
		ft_custom_error_exit("Minishell: export: no env or not a valid \
argument");
	i = 0;
	success = 0;
	while (args[i])
	{
		success += new_var(data->envp, args[i]);
		i++;
	}
	return (success);
}
