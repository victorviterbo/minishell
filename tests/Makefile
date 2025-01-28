# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 12:45:22 by vviterbo          #+#    #+#              #
#    Updated: 2025/01/28 19:12:07 by vviterbo         ###   ########.fr        #
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

tests: test_echo test_cd_pwd test_env

test_echo: $(SRCS) $(LIBFT) test_echo.c
	@$(CC) $(CFLAGS) $(INCLUDE) $(MINI_SRCS) test_echo.c -o $(BIN)test_echo

test_cd_pwd: $(SRCS) $(LIBFT) test_cd_pwd.c
	@$(CC) $(CFLAGS) $(INCLUDE) $(MINI_SRCS) test_cd_pwd.c -o $(BIN)test_cd_pwd

test_env: $(SRCS) $(LIBFT) test_env.c
	@$(CC) $(CFLAGS) $(INCLUDE) $(MINI_SRCS) test_env.c -o $(BIN)test_env

clean:
	$(MAKE) -C ../ clean
	rm -f objs/*.o

fclean: clean
	$(MAKE) -C ../ fclean
	rm -f $(BIN)*

re: fclean all

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_SRCS)
	$(MAKE) -C $(LIBFT_DIR) all

.PHONY: all clean fclean re
