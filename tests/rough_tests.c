/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rough_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/17 22:47:21 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*here;

	here = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    (void)argc;
    (void)argv;
    (void)envp;
    ft_echo("print this string with newline", false);
    ft_echo("print this string without newline", true);
    ft_echo("print this string \n with newline", false);
	here = getcwd(here, BUFFER_SIZE);
	ft_printf("your current path is : %s\n", ft_cwd());
	ft_cd("testdir");
	//ft_cd("tesuh");
	chdir(here);
	ft_cd("rough_tests.c");
    return (0);
}
