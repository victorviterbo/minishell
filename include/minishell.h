/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:04:30 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/01 00:43:55 by vbronov          ###   ########.fr       */
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
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <fcntl.h>

# include "libft.h"

# ifndef DEBUG
#  define DEBUG 0
# endif
# define SHELL_NAME "Minishell: "
# define SHELL_PROMPT "Minishell$ "
# define DEFAULT_ERROR "an unknown error has occured"
# define FALSE		0
# define TRUE		1
# define EXIT_NUMARG 2

enum e_quotes
{
	IS_NOT_QUOTED,
	IS_SINGLE_QUOTED,
	IS_DOUBLE_QUOTED
};

enum e_signal
{
	READLINE_MODE,
	EXECUTION_MODE,
	INSIGINT,
	INSIGQUIT,
};

enum e_token_type
{
	PIPE,
	OPENPAR,
	CLOSEPAR,
	AND,
	OR,
	WORD,
	STDOUT,
	STDOUT_APPEND,
	STDIN,
	STDIN_HEREDOC
};

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_leaf
{
	int		fdin;
	int		fdout;
	char	*limiter;
	char	**args;
}	t_leaf;

struct s_data;
typedef int	(*t_pfunc)(struct s_data *data, char *args[], int argc);

typedef struct s_builtin
{
	char	*name;
	t_pfunc	func;
}	t_builtin;

typedef struct s_data
{
	t_list		**envp;
	char		**env_arr;
	t_token		*tokens;
	int			exit_status;
	int			last_exit;
	t_tree		*tree;
	t_builtin	builtins[8];
}	t_data;

typedef struct s_var
{
	char	*name;
	char	*value;
}	t_var;

// EXEC
//exec/echo.c
int		ft_echo(t_data *data, char **args, int argc);
//exec/cd.c
int		ft_cd(t_data *data, char **args, int argc);
char	*get_absolute_path(t_data *data, char *path);
//exec/env.c
int		ft_env(t_data *data, char **args, int argc);
//exec/export.c
int		ft_export(t_data *data, char **args, int argc);
int		export_no_args(t_data *data);
//exec/pwd.c
int		ft_pwd(t_data *data, char **args, int argc);
char	*ft_get_current_path(t_data *data);
//exec/unset.c
int		ft_unset(t_data *data, char **args, int argc);
void	pop_var(t_data *data, char *varname);
void	free_var(void *data);
//exec/execve.c
void	ft_execve(t_data *data, char **args);
char	*find_exec(t_data *data, char *path_list, char *exec);
void	init_builtin(t_data *data);
//exec/exit.c
int		ft_exit(t_data *data, char **args, int argc);
void	free_all(t_data *data);
void	free_env(t_data *data);
//exec/run_ast.c
int		ft_run_ast(t_data *data, t_tree *node);
int		handle_command(t_data *data, t_leaf *leaf);

// PARSING
//parsing/build_tree.c
void	make_ast(t_data *data, t_token *token);
void	ast_trav(t_data *data, t_tree *tree);
void	build_tree(t_token *token, t_tree *tree, bool openpar);
void	explore_tree(t_token *token, t_token *current, t_token *last,
			t_tree *tree);
void	make_leaf(t_data *data, t_token *current, t_leaf *leaf);
//parsing/parse.c
char	*parse_str(t_data *data, char *str, bool inplace);
//parsing/expand.c
char	*expand_var(t_data *data, char *str, int *isescaped);
char	*replace_var(t_data *data, char *str, size_t *i, size_t *j);
char	*get_varname(t_data *data, char *str, size_t *i, size_t *j);
//parsing/lexer.c
t_token	*lexer(t_data *data, char *str);

// STREAM
//stream/set_stream.c
int		open_stream(t_data *data, t_leaf *leaf, t_token *token);

// UTILS
//utils/ast_utils.c
void	tree_error_leaf(t_leaf *leaf, t_tree *tree);
void	tree_error_token(t_token *token, t_tree *tree);
void	free_leaf(t_leaf *leaf);
t_pfunc	is_builtin(char *str, t_builtin *builtin);
//utils/env_to_arr.c
char	**env_to_arr(t_data *data);
char	*var_to_str(t_data *data, t_list *current);
void	update_env_arr(t_data *data);
void	change_shlvl(t_data *data, int change);
void	*copy_var(void	*var);
//utils/env_utils.c
void	init_env(t_data *data, char **envp);
//utils/error_handlings.c
void	ft_error(t_data *data, const char *message);
//utils/parsing_utils.c
int		*is_quote_escaped(t_data *data, char *str);
char	*remove_quotes_ws(t_data *data, char *str, int *isescaped,
			bool inplace);
size_t	go_to_next(char *str, char *chars, size_t i);
//utils/token_utils.c
t_token	*lexer_error(t_data *data, t_token *head, t_token *current);
void	free_token(void *content);
void	free_tokens(t_token *head);
//utils/variables.c
void	new_var(t_data *data, char *str);
void	add_var(t_data *data, t_list **env, char *str, size_t name_len);
void	change_var(t_data *data, t_list *current, char *first_equal,
			bool append);
char	*get_var(t_data *data, char *varname);
char	*get_last_exit_status(t_data *data);
//utils/print_utils.c
void	display_tree(t_tree *node);
void	print_tokens(t_token *tokens);

// MAIN
int		disable_echoctl(int disable);

#endif