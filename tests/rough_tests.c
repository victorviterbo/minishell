/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rough_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/15 17:15:02 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

void	ft_echo(char *str, bool no_nl);

int main(int argc, char *argv[], char *envp[])
{
    (void)argc;
    (void)argv;
    (void)envp;
    ft_echo("print this string with newline", false);
    ft_echo("print this string without newline", true);
    ft_echo("print this string \n with newline", false);
    return (0);
}