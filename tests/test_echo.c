/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/25 20:10:19 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_make_test_strarr(char *str);

int	main(int argc, char *argv[], char *envp[])
{

	(void)argc;
	(void)argv;
	(void)envp;
	ft_echo("print this string with newline", false);
	ft_echo("print this string without newline", true);
	ft_echo("print this string \n with newline", false);
	ft_echo(NULL, true);
	ft_echo(NULL, false);
	return (0);
}
