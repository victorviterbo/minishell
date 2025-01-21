/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:04:30 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/21 17:15:04 by vviterbo         ###   ########.fr       */
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

typedef struct s_variable {
	char	*name;
	char	*value;
}	t_variable;

int		ft_echo(char *str, bool no_nl);

int		ft_cd(char *path);
char	*get_absolute_path(char *path);

int		ft_pwd(void);
char	*ft_get_current_path(void);

int		ft_export(char *args[], char *envp[]);
int		change_envp(char *str, char *envp[], bool append);
int		rewrite_var(char *str, char *envp[], int i, bool append);

void	ft_perror_exit(const char *message);
void	ft_custom_error_exit(const char *message);

t_list	**env2lst(char *envp[]);
void	print_env(char *envp[]);

#endif