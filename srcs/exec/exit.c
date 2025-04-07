/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:26:46 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/07 13:15:47 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: add missing logic:
//  * handle exit status that should be between 0 and 255
//  * handle negative numbers
//  * argv[0] is the command name, argv[1] is the exit status
//  * if no arguments are passed, the exit status is the last command status
int	ft_exit(t_data *data, char **args, int argc)
{
	int	i;

	ft_printf("exit\n");
	if (argc > 2)
		return (ft_error(data, "exit: too many arguments"), EXIT_FAILURE);
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
	free_all(data);
	ft_free_array((void **)args, argc);
	exit(data->exit_status);
}

void	free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->tree)
		free_tree(data->tree);
	data->tree = NULL;
	if (data->tokens)
		free_tokens(data->tokens);
	data->tokens = NULL;
	free_env(data);
}

void	free_env(t_data *data)
{
	if (!data)
		return ;
	if (data->envp)
	{
		ft_lstclear(data->envp, free_var);
		free(data->envp);
	}
	data->envp = NULL;
	if (data->env_arr)
		ft_free_array((void **)data->env_arr, ft_arrlen(data->env_arr));
	data->env_arr = NULL;
}
