/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:04:30 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/21 13:23:06 by vviterbo         ###   ########.fr       */
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

# define SHELL_NAME "Minishell: "
# define SHELL_PROMPT "Minishell$ "
# define DEFAULT_ERROR "an unknown error has occured"

enum e_QUOTES {
	IS_NOT_QUOTED,
	IS_SINGLE_QUOTED,
	IS_DOUBLE_QUOTED
};

typedef struct s_data
{
	t_list	**envp;
	char	**env_arr;
	int		exit_status;
}	t_data;

typedef struct s_var
{
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
//exec/env.c
int		ft_env(t_data *data);
//exec/execve.c
int		ft_execve(t_data *data, char **args);
char	*find_exec(char *path_list, char *exec);
//parsing/build_tree.c
void	build_tree(char *str, t_tree *tree);
char	*is_cmd_separator(char c1, char c2, bool openpar);
void	explore_subtree(t_tree *tree, char *str, size_t i, size_t seplen);
//parsing/parse.c
char	*parse_str(t_data *data, char *str);
//parsing/expand.c
char	*expand_var(t_data *data, char *str, int *isescaped);
char	*replace_var(t_data *data, char *str, size_t *i, size_t *j);
//utils/env_to_arr.c
char	**env_to_arr(t_data *data);
char	*var_to_str(t_list *current);
void	update_env_arr(t_data *data);
void	change_shlvl(t_data *data, int change);
void	*copy_var(void	*var);
//utils/error_handlings.c
void	ft_print_error(const char *message);
//utils/parsing_utils.c
bool	*is_quoted(char *str, char open_char, char close_char);
int		*is_quote_escaped(char *str);
char	*remove_quotes_ws(char *str, int *isescaped, bool inplace);
size_t	go_to_next(char *str, char *chars, size_t i);
//utils/variables.c
int		init_env(t_data *data, char **envp);
int		new_var(t_data *data, char *str);
int		add_var(t_data *data, t_list **env, char *str, size_t name_len);
int		change_var(t_data *data, t_list *current, char *first_equal,
			bool append);
char	*get_var(t_data *data, char *varname);

#endif