/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:04:30 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/26 15:16:14 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>

# include <stdio.h>

typedef struct s_env {
	t_list	**envp;
}	t_env;

typedef struct s_var{
	char	*name;
	char	*value;
}	t_var;

//exec/echo.c
int		ft_echo(char *str, bool no_nl);
//exec/cd.c
int		ft_cd(char *path);
char	*get_absolute_path(char *path);
//exec/pwd.c
int		ft_pwd(void);
char	*ft_get_current_path(void);
//exec/export.c
int		ft_export(char *args[], t_env *env);
int		change_envp(char *str, t_env *env, bool append);
int		rewrite_var(char *str, t_env *env, int i, bool append);

void	ft_perror_exit(const char *message);
void	ft_custom_error_exit(const char *message);

void	print_env(char *envp[]);

#endif