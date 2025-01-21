# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 12:45:22 by vviterbo          #+#    #+#              #
#    Updated: 2025/01/21 14:03:09 by vviterbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = minishell.h

CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft/

LIBFT_SRCS = $(addprefix libft/, $(shell make -C libft/ -s print_srcs))

LIBFT = $(LIBFT_DIR)libft.a

EXEC_F		=	cd.c echo.c pwd.c export.c
SRCS_EXEC	=	$(addprefix exec/, $(EXEC_F))

UTILS_F		= 	error_handling.c
SRCS_UTILS	=	$(addprefix utils/, $(UTILS_F))

SRCS = $(SRCS_EXEC) $(SRCS_UTILS)

CC = cc

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
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -lft $(SRCS) tests/rough_tests.c -o $(NAME)

.PHONY: all clean fclean re
