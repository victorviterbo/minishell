/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:04:30 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/18 00:08:03 by vviterbo         ###   ########.fr       */
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
# include <string.h>
# include <dirent.h>

# include "libft.h"

# ifndef DEBUG
#  define DEBUG 0
# endif
# define SHELL_NAME "minishell"
# define SHELL_PROMPT "minishell$ "
# define DEFAULT_ERROR "an unknown error has occured"
# define FALSE		0
# define TRUE		1
# define PIPE_OUT	0
# define PIPE_IN	1
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
};

typedef enum e_token_type
{
	WORD,
	STDOUT,
	STDOUT_APPEND,
	STDIN,
	STDIN_HEREDOC,
	PIPE,
	OPENPAR,
	CLOSEPAR,
	AND,
	OR,
	CMD,
}	t_token_type;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_node
{
	int				type;
	t_token			*redi;
	t_token			*args;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

// TODO: delete it later
typedef struct s_leaf
{
	int		fdin;
	int		fdout;
	char	*limiter;
	char	**args;
}	t_leaf;

struct		s_data;
typedef int	(*t_pfunc)(struct s_data *data, char *args[], int argc);

typedef struct s_builtin
{
	char	*name;
	t_pfunc	func;
}	t_builtin;

typedef struct s_data
{
	t_list			**envp;
	char			**env_arr;
	t_token			*tokens;
	int				exit_status;
	int				last_exit_status;
	struct s_node	*tree;
	t_builtin		builtins[8];
	int				saved_streams[2];
}	t_data;

typedef struct s_var
{
	char	*name;
	char	*value;
}	t_var;

// EXEC
//exec/echo.c
int				ft_echo(t_data *data, char **args, int argc);
//exec/cd.c
int				ft_cd(t_data *data, char **args, int argc);
char			*get_absolute_path(t_data *data, char *path);
//exec/env.c
int				ft_env(t_data *data, char **args, int argc);
//exec/export.c
int				ft_export(t_data *data, char **args, int argc);
int				export_no_args(t_data *data);
//exec/fork.c
int				create_pipe_process(t_data *data, t_node *node, int *pipefds,
					int fd_dst);
//exec/pipe.c
int				init_pipe(t_data *data, int pipefds[2]);
void			close_pipe(t_data *data, int pipe[2]);
int				handle_pipex(t_data *data, t_node *node);
//exec/pwd.c
int				ft_pwd(t_data *data, char **args, int argc);
char			*ft_get_current_path(t_data *data);
//exec/redir.c
int				save_std_streams(t_data *data);
int				restore_std_streams(t_data *data, int saved_streams[2]);
//exec/unset.c
int				ft_unset(t_data *data, char **args, int argc);
void			pop_var(t_data *data, char *varname);
void			free_var(void *data);
//exec/execve.c
void			get_exec_path(t_data *data, char **args);
char			*find_exec(t_data *data, char *path_list, char *exec);
int				exec_non_builtin(t_data *data, char **args);
void			init_builtin(t_data *data);
//exec/exit.c
int				ft_exit(t_data *data, char **args, int argc);
void			free_all(t_data *data);
void			free_env(t_data *data);
//exec/run_ast.c
int				ft_run_ast(t_data *data, t_node *node);
int				handle_command(t_data *data, t_node *node);
//exec/wait.c
int				wait_pid(t_data *data, int child_pid);

// PARSING
//parsing/build_ast_helpers.c
t_node			*handle_cmd(t_data *data, t_token *start, t_token *end);
t_node			*handle_operator(t_data *data, t_token *start, t_token *end,
					t_token *op_token);
//parsing/build_ast.c
t_node			*build_tree(t_data *data, t_token *start, t_token *end);
//parsing/parse.c
char			**parse_str(t_data *data, char *str, t_token_type type);
//parsing/expand.c
char			*expand_var(t_data *data, char *str, int *isescaped);
int				replace_var(t_data *data, char *str, char *expanded, size_t *j);
char			*get_varname(t_data *data, char *str, size_t *j);
char			*dry_run_allocate(t_data *data, char *str, int *isescaped);
void			dry_run_skip_var(t_data *data, char *str, size_t *new_size,
					size_t *i);
char			*parse_varname(t_data *data, char *str, size_t *j);
//parsing/lexer.c
void			lexer(t_data *data, char *str);
//parsing/syntax_check.c
int				syntax_check(t_data *data, t_token *tokens);
//parsing/wildcard.c
char			**wildcard_handle(t_data *data, char *parsed, int *isescaped,
					t_token_type type);
char			**substitute_wildcard(t_data *data, char *str, int *isescaped);
char			**ls_curr_dir(t_data *data);
char			**add_fname_to_arr(t_data *data, const char *fname,
					char **files);
char			**filter_sort_matches(t_data *data, char **candidates,
					char *pattern, int *isescaped);
bool			is_wildcard_match(char *pattern, char *candidate,
					int *isescaped);

// STREAM
//stream/set_stream.c
int				open_stream(t_data *data, t_leaf *leaf, t_token *token);

// UTILS
//utils/ast_utils.c
t_node			*new_tree_node(t_data *data, char type);
void			free_tree(t_node *node);
t_pfunc			is_builtin(char *str, t_builtin *builtin);
unsigned int	token_list_size(t_token *list);
char			**token_list_to_args(t_data *data, t_token *token_list);
//utils/env_to_arr.c
char			*var_to_str(t_data *data, t_list *current);
void			update_env_arr(t_data *data);
void			change_shlvl(t_data *data, int change);
void			*copy_var(void	*var);
//utils/env_utils.c
void			init_env(t_data *data, char **envp);
//utils/error_handlings.c
void			ft_error(t_data *data, const char *message);
//utils/parsing_utils.c
int				*is_quote_escaped(t_data *data, char *str);
void			remove_quotes(char *str, int *isescaped);
size_t			go_to_next(char *str, char *chars, size_t i);
//utils/token_utils.c
void			free_token(void *content);
void			free_tokens(t_token *head);
t_token			*copy_token(t_data *data, t_token *token);
void			push_back_token(t_token **list, t_token *token);
void			print_tokens(t_token *tokens);
//utils/variables.c
void			new_var(t_data *data, char *str);
void			add_var(t_data *data, t_list **env, char *str, size_t name_len);
void			change_var(t_data *data, t_list *current, char *first_equal,
					bool append);
char			*get_var(t_data *data, char *varname);
char			*get_last_exit_status(t_data *data, char *varname);
//utils/print_utils.c
void			display_tree(t_node *node);
//utils/wildcard_utils.c
char			**merge_strarr(t_data *data, char **arr1, char **arr2,
					t_Inplace_Type inplace);
int				handle_match(t_data *data, t_list **matches, char *new_match);
//utils/wildcard_sort_utils.c
char			**sort_matches(t_data *data, t_list **matches);
//utils/signal_utils.c
void			set_signal(int signum, void (*handler)(int));
//utils/string_utils.c
const char		*node_type_to_string(enum e_token_type type);

#endif