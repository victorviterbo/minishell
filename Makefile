# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 12:45:22 by vviterbo          #+#    #+#              #
#    Updated: 2025/01/17 23:04:41 by vviterbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = minishell.h

CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft/

LIBFT_SRCS = $(patsubst %.c, ../%.c, $(shell make -C libft/ -s print_srcs))

LIBFT = $(LIBFT_DIR)libft.a

SRCS_EXEC =	cd.c echo.c pwd.c 

SRCS_UTILS = error_handling.c

SRCS =	

OBJS = $(patsubst %.c, %.o, $(SRCS))

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
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(LIBFT): $(LIBFT_SRCS)
	$(MAKE) -C $(LIBFT_DIR) all

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) -L$(LIBFT_DIR) -lft -o $(NAME)

.PHONY: all clean fclean re
