/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:04:30 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/26 20:15:54 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>

# include <stdio.h>

typedef struct s_data {
	t_list	**envp;
}	t_data;

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
int		ft_export(char *args[], t_data *env);
//utils/error_handlings.c
void	ft_perror_exit(const char *message);
void	ft_custom_error_exit(const char *message);
//utils/variables.c
int		init_env(char **envp, t_data *data);
int		new_var(t_list **env, char *str);
int		dd_var(t_list **env, char *str, size_t name_len);
int		change_var(t_list *current, char *first_equal, bool append);

#endif