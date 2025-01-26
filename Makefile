# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 12:45:22 by vviterbo          #+#    #+#              #
#    Updated: 2025/01/26 14:57:51 by vviterbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = minishell.h

CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./lib/libft/

LIBFT_SRCS = $(addprefix $(LIBFT_DIR), $(shell make -C $(LIBFT_DIR) -s print_srcs))

LIBFT = $(LIBFT_DIR)libft.a

EXEC_F		=	cd.c echo.c pwd.c export.c
SRCS_EXEC	=	$(addprefix exec/, $(EXEC_F))

UTILS_F		= 	error_handling.c
SRCS_UTILS	=	$(addprefix utils/, $(UTILS_F))

SRCS = $(addprefix srcs/, $(SRCS_EXEC) $(SRCS_UTILS))

BIN = ./bin/

CC = cc

INCLUDE = -I./include/ -I./lib/ -L$(LIBFT_DIR) -lft

all: objs_folder $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f objs/*.o

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

objs_folder :
	@mkdir -p objs/

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_SRCS)
	$(MAKE) -C $(LIBFT_DIR) all

$(NAME): $(SRCS) tests/rough_tests.c $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) tests/rough_tests.c -o $(BIN)$(NAME)

.PHONY: all clean fclean re
