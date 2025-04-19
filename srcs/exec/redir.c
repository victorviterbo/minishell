/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 07:38:41 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/19 01:51:27 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect(t_data *data, int redi_fd, char *path, int flags)
{
	int	fd;

	fd = open(path, flags, 0664);
	if (fd == -1)
		return (ft_error(data, "open"), data->exit_status);
	if (dup2(fd, redi_fd) == -1)
		ft_error(data, "dup2");
	close(fd);
	return (data->exit_status);
}

void	check_redirections(t_data *data, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!is_redir_token(args[i]) && args[i + 1] == NULL)
			return (ft_error(data, "ambiguous redirect"));
		if (args[i + 1] == NULL)
		{
			ft_error(data, "syntax error near unexpected token 'newline'");
			data->exit_status = EXIT_NUMARG;
			return ;
		}
		if (is_redir_token(args[i]) && is_redir_token(args[i + 1]))
		{
			ft_fprintf(STDERR_FILENO,
				"%s: syntax error near unexpected token `%s'\n",
				SHELL_NAME, args[i + 1]);
			data->exit_status = EXIT_NUMARG;
			return ;
		}
		if (!is_redir_token(args[i]) && !is_redir_token(args[i + 1]))
			return (ft_error(data, "ambiguous redirect"));
		i += 2;
	}
}

static int	process_redirections(t_data *data, char **args)
{
	while (*args)
	{
		if ((*args)[0] == '<')
		{
			if (redirect(data, STDIN_FILENO, *(args + 1), O_RDONLY))
				return (EXIT_FAILURE);
		}
		else if ((*args)[0] == '>' && (*args)[1] == '>')
		{
			if (redirect(data, STDOUT_FILENO, *(args + 1),
					O_CREAT | O_WRONLY | O_APPEND))
				return (EXIT_FAILURE);
		}
		else if ((*args)[0] == '>')
		{
			if (redirect(data, STDOUT_FILENO, *(args + 1),
					O_CREAT | O_WRONLY | O_TRUNC))
				return (EXIT_FAILURE);
		}
		else
			return (ft_error(data, NULL), EXIT_FAILURE);
		args += 2;
	}
	return (EXIT_SUCCESS);
}

void	apply_redirections(t_data *data, t_token *redi)
{
	char	**args;

	args = token_list_to_args(data, redi);
	if (!args)
		return ;
	check_redirections(data, args);
	if (data->exit_status)
		return (ft_free_array((void **)args, ft_arrlen(args)));
	if (process_redirections(data, args))
		return (ft_free_array((void **)args, ft_arrlen(args)));
	ft_free_array((void **)args, ft_arrlen(args));
}
