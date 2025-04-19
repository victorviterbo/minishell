# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 12:45:22 by vviterbo          #+#    #+#              #
#    Updated: 2025/04/19 02:09:30 by vbronov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = minishell.h

CFLAGS = -g -fsanitize=address -Wall -Wextra -Werror 

ifdef DEBUG
    CFLAGS += -DDEBUG=1 -g
endif

LIBFT_DIR = ./lib/libft/

LIBFT_SRCS = $(addprefix $(LIBFT_DIR), $(shell make -C $(LIBFT_DIR) -s print_srcs))

LIBFT = $(LIBFT_DIR)libft.a

EXEC_F		=	cd.c echo.c pwd.c export.c unset.c env.c execve.c exit.c \
				run_ast.c redir.c pipe.c fork.c wait.c std_redir.c
SRCS_EXEC	=	$(addprefix exec/, $(EXEC_F))

PARSING_F		= 	expand.c parse.c build_ast_helpers.c build_ast.c lexer.c \
					syntax_check.c wildcard.c
SRCS_PARSING	=	$(addprefix parsing/, $(PARSING_F))

UTILS_F		= 	error_utils.c variables.c env_to_arr.c parsing_utils.c \
				ast_utils.c token_utils.c env_utils.c print_utils.c \
				string_utils.c signal_utils.c wildcard_utils.c \
				wildcard_sort_utils.c syntax_check_utils.c
SRCS_UTILS	=	$(addprefix utils/, $(UTILS_F))

SRCS = $(addprefix srcs/, $(SRCS_EXEC) $(SRCS_UTILS) $(SRCS_PARSING))

BIN = ./bin/

CC = cc

INCLUDE = -I./include/ -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft -lreadline

all: folders $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f objs/*.o

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(BIN)$(NAME)

re: fclean all

folders :
	@mkdir -p objs/
	@mkdir -p bin/

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_SRCS)
	@$(MAKE) -C $(LIBFT_DIR) all

$(NAME): $(SRCS)
	@$(MAKE) -C $(LIBFT_DIR) all
	@$(CC) $(CFLAGS) $(SRCS) ./srcs/minishell.c $(INCLUDE) -o $(BIN)$(NAME)
	@echo "Minishell compiled successfully"

print_srcs:
	@echo $(SRCS)

leak:
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=all --suppressions=ignore_readline_leaks.supp $(BIN)$(NAME)

.PHONY: all clean fclean re
