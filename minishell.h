/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:04:30 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/17 22:48:25 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>

# include <stdio.h>

int		ft_echo(char *str, bool no_nl);

int		ft_cd(char *path);
char	*get_absolute_path(char *path);

char	*ft_pwd(void);



void	ft_perror_exit(const char *message);
void	ft_custom_error_exit(const char *message);

#endif