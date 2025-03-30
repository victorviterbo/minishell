/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:26:46 by vbronov           #+#    #+#             */
/*   Updated: 2025/03/15 17:19:07 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: add missing logic:
//  * free all malloced memory
//  * handle exit status that should be between 0 and 255
//  * handle negative numbers
//  * argv[0] is the command name, argv[1] is the exit status
//  * if no arguments are passed, the exit status is the last command status
//  * this fuction supposed to have monogamic signature in order to simplify builtins handling
void	ft_exit(t_data *data, char **args, int argc)
{
	int i;

	ft_printf("exit\n");
	if (argc > 2)
		return (ft_error(data, "exit: too many arguments\n"));
	disable_echoctl(FALSE);
	if (argc == 2)
	{
		i = 0;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				ft_fprintf(2, "exit: %s: numeric argument required\n", args[1]);
				exit(EXIT_NUMARG);
			}
			i++;
		}
		data->exit_status = ft_atoi(args[1]);
	}
	// TODO: free all malloced memory
	exit(data->exit_status);
}
