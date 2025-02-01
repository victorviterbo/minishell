/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:04:30 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/01 12:37:59 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <stdio.h>

# include "libft.h"

typedef struct s_data {
	t_list	**envp;
}	t_data;

typedef struct s_var{
	char	*name;
	char	*value;
}	t_var;

//exec/echo.c
int		ft_echo(char *str, bool nl);
//exec/cd.c
int		ft_cd(t_data *data, char *path);
char	*get_absolute_path(char *path);
//exec/env.c
int		ft_env(t_data *data);
//exec/export.c
int		ft_export(t_data *env, char *args[]);
//exec/pwd.c
int		ft_pwd(void);
char	*ft_get_current_path(void);
//exec/unset.c
int		ft_unset(t_data *data, char **varnames);
int		pop_var(t_data *data, char *varname);
void	free_var(void *data);

//utils/env_to_arr.c
char	**env_to_arr(t_data *data);
char	*var_to_str(t_list *current);
//utils/error_handlings.c
void	ft_perror_exit(const char *message);
void	ft_custom_error_exit(const char *message);
//utils/parsing_utils.c
bool	*is_quoted(char *str, char open_char, char close_char);
//utils/variables.c
int		init_env(t_data *data, char **envp);
int		new_var(t_list **env, char *str);
int		add_var(t_list **env, char *str, size_t name_len);
int		change_var(t_list *current, char *first_equal, bool append);
char	*get_var(t_data *data, char *varname);

#endif