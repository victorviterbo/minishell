/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:26:46 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/17 19:51:32 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_number(char *str)
{
	int		i;
	int		sign;
	size_t	len;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	len = ft_strlen(&str[i]);
	if (len > 19)
		return (FALSE);
	if (len == 19)
	{
		if (sign == 1 && ft_strcmp(&str[i], "9223372036854775807") > 0)
			return (FALSE);
		if (sign == -1 && ft_strcmp(&str[i], "9223372036854775808") > 0)
			return (FALSE);
	}
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (FALSE);
	return (TRUE);
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
	//rl_clear_history();
	close_pipe(data, data->saved_streams);
}

int	ft_exit(t_data *data, char **args, int argc)
{
	ft_printf("exit\n");
	if (argc > 2)
		return (ft_error(data, "exit: too many arguments"), EXIT_FAILURE);
	if (argc == 2)
	{
		if (!is_valid_number(args[1]))
		{
			ft_fprintf(2, "%s: exit: %s: numeric argument required\n", \
				SHELL_NAME, args[1]);
			data->exit_status = EXIT_NUMARG;
		}
		else
			data->exit_status = ft_atoi(args[1]) & 0xFF;
	}
	free_all(data);
	ft_free_array((void **)args, argc);
	exit(data->exit_status);
}
