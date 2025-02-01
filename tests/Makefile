# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 12:45:22 by vviterbo          #+#    #+#              #
#    Updated: 2025/02/06 20:21:38 by vviterbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = minishell.h

CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ../lib/libft/

MINI_DIR = ../

MINI_SRCS =  $(addprefix $(MINI_DIR), $(shell make -C $(MINI_DIR) -s print_srcs))

LIBFT_SRCS = $(addprefix $(LIBFT_DIR), $(shell make -C $(LIBFT_DIR) -s print_srcs))

LIBFT = $(LIBFT_DIR)libft.a

BIN = ./bin/

CC = cc

INCLUDE = -I../include/ -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft

SRCS = $(addprefix srcs/, $(SRCS_EXEC) $(SRCS_UTILS))

all: tests
	@$(MAKE) -C ../ all

tests:	folders test_echo test_cd_pwd test_env test_execve test_execve_leaks \
		test_parsing

test_echo: $(SRCS) $(LIBFT) test_echo.c
	@$(CC) $(CFLAGS) $(MINI_SRCS) test_echo.c $(INCLUDE) -o $(BIN)test_echo

test_cd_pwd: $(SRCS) $(LIBFT) test_cd_pwd.c
	@$(CC) $(CFLAGS) $(MINI_SRCS) test_cd_pwd.c $(INCLUDE) -o $(BIN)test_cd_pwd

test_env: $(SRCS) $(LIBFT) test_env.c
	@$(CC) $(CFLAGS) $(MINI_SRCS) test_env.c $(INCLUDE) -o $(BIN)test_env

test_execve: $(SRCS) $(LIBFT) test_execve.c
	@$(CC) $(CFLAGS) $(MINI_SRCS) test_execve.c $(INCLUDE) -o $(BIN)test_execve
	
test_execve_leaks: $(SRCS) $(LIBFT) test_execve_leaks.c
	@$(CC) $(CFLAGS) $(MINI_SRCS) test_execve_leaks.c $(INCLUDE) -o $(BIN)test_execve_leaks

test_parsing: $(SRCS) $(LIBFT) test_parsing.c
	@$(CC) $(CFLAGS) $(INCLUDE) $(MINI_SRCS) test_parsing.c -o $(BIN)test_parsing

clean:
	$(MAKE) -C ../ clean

fclean: clean
	$(MAKE) -C ../ fclean
	rm -fr $(BIN)*

re: fclean all

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_SRCS)
	$(MAKE) -C $(LIBFT_DIR) all

folders :
	@mkdir -p bin/
	@mkdir -p out/

.PHONY: all clean fclean re
