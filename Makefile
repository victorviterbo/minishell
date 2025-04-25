# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 12:45:22 by vviterbo          #+#    #+#              #
#    Updated: 2025/04/25 19:04:10 by vviterbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bin/minishell

HEADER = minishell.h

CFLAGS = -Wall -Wextra -Werror -g

ifdef SANITIZE
    SANITIZE_FLAGS = -fsanitize=address
else
    SANITIZE_FLAGS =
endif

ifdef DEBUG
	CFLAGS += -DDEBUG=1
endif

LIBFT_DIR = ./lib/libft/

LIBFT_SRCS = $(addprefix $(LIBFT_DIR), $(shell make -C $(LIBFT_DIR) -s print_srcs))

LIBFT = $(LIBFT_DIR)libft.a

EXEC_F		=	cd.c echo.c pwd.c export.c unset.c env.c execve.c exit.c \
				run_ast.c redir.c pipe.c fork.c wait.c std_redir.c redir_check.c \
				redir_heredoc_handler.c redir_heredoc.c
SRCS_EXEC	=	$(addprefix exec/, $(EXEC_F))

PARSING_F		= 	expand.c parse.c build_ast_helpers.c build_ast.c lexer.c \
					syntax_check.c wildcard.c
SRCS_PARSING	=	$(addprefix parsing/, $(PARSING_F))

UTILS_F		= 	error_utils.c variables.c env_to_arr.c parsing_utils.c \
				ast_utils.c token_utils.c env_utils.c print_utils.c \
				string_utils.c signal_utils.c wildcard_utils.c \
				args_utils.c syntax_check_utils.c path_utils.c \
				expand_utils.c variable_utils.c
SRCS_UTILS	=	$(addprefix utils/, $(UTILS_F))

SRCS = $(addprefix srcs/, $(SRCS_EXEC) $(SRCS_UTILS) $(SRCS_PARSING)) srcs/minishell.c

BIN = ./bin/
OBJ_DIR = ./objs/

OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)

CC = cc

INCLUDE = -I./include/ -I$(LIBFT_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline

all: folders $(LIBFT) $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

bonus: all

folders:
	@mkdir -p $(OBJ_DIR)srcs/exec
	@mkdir -p $(OBJ_DIR)srcs/parsing
	@mkdir -p $(OBJ_DIR)srcs/utils
	@mkdir -p $(BIN)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "Minishell compiled successfully"

print_srcs:
	@echo $(SRCS)

print_objs:
	@echo $(OBJS)

leak:
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=all --suppressions=ignore_readline_leaks.supp $(NAME)

.PHONY: all clean fclean re folders print_srcs print_objs leak bonus
