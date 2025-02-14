/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:25:55 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 11:37:44 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void		print_boolarray(bool *arr, char *str);
static void	test_is_quoted(char *str, bool expected_NULL, char c1, char c2);
static void	test_expand(t_data *data, char *str);

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	char	**args;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	init_env(data, envp);

	test_is_quoted("\"What if it starts\" with a quoted \"string\"", false, '"', '"');
	test_is_quoted("and with 'other quoting chars'?", false, '\'', '\'');
	test_is_quoted("and \"unfinished quotes ?", true, '"', '"');
	test_is_quoted("what about {braces}", false, '{', '}');
	test_is_quoted("and in reverse {braces} now", true, '}', '{');
	test_expand(data, "Just a string\n", false);
	test_expand(data, "Just a string with a $VAR\n", false);
	args = ft_make_test_strarr("VAR=var");
	ft_export(data, args);
	free(args);
	test_expand(data, "Just a string with a $VAR\n", false);
	test_expand(data, "Just a string with a \"$VAR\"\n", false);
	test_expand(data, "Just a string with a '$VAR'\n", false);
	test_expand(data, "Just a string with a '${VAR}'\n", false);
	test_expand(data, "Just a string with a ${VAR}\n", false);
	test_expand(data, "Just a string with a ${VAR}$VAR\n", false);
	test_expand(data, "Just a string with a '${VAR}'\n", false);
	test_expand(data, "\"Just a string with a '${VAR}'\"\n", false);
	test_expand(data, "\"Just a string with a '${VAR}\"'\n", true);
	free_env(data);
	return (EXIT_SUCCESS);
}

void	print_boolarray(bool *arr, char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		ft_printf("%c", str[i]);
		if (i + 1 < ft_strlen(str))
			ft_printf(", ");
		i++;
	}
	ft_printf("\n", arr[i]);
	i = 0;
	while (i < ft_strlen(str))
	{
		ft_printf("%i", arr[i]);
		if (i + 1 < ft_strlen(str))
			ft_printf(", ");
		i++;
	}
	ft_printf("\n\n");
}

static void	test_is_quoted(char *str, bool expected_NULL, char c1, char c2)
{
	bool	*isquoted;

	isquoted = is_quoted(str, c1, c2);
	if (expected_NULL)
	{
		if (isquoted != NULL)
		{
			free(isquoted);
			exit(EXIT_FAILURE);
		}
		else
			return ;
	}
	print_boolarray(isquoted, str);
	free(isquoted);
}

static void	test_expand(t_data *data, char *str, bool expected_fail)
{
	char	*expanded;
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid == 0)
	{
		expanded = parse_str(data, str);
	}
	waitpid(pid, &exit_status, 0);
	if (expected_fail == (exit_status != 0))
	ft_printf("%s", expanded);
	free(expanded);
}
