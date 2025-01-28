# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 12:45:22 by vviterbo          #+#    #+#              #
#    Updated: 2025/01/28 20:40:42 by vviterbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = minishell.h

CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./lib/libft/

LIBFT_SRCS = $(addprefix $(LIBFT_DIR), $(shell make -C $(LIBFT_DIR) -s print_srcs))

LIBFT = $(LIBFT_DIR)libft.a

EXEC_F		=	cd.c echo.c pwd.c export.c unset.c env.c
SRCS_EXEC	=	$(addprefix exec/, $(EXEC_F))

UTILS_F		= 	error_handling.c variables.c
SRCS_UTILS	=	$(addprefix utils/, $(UTILS_F))

SRCS = $(addprefix srcs/, $(SRCS_EXEC) $(SRCS_UTILS))

BIN = ./bin/

CC = cc

INCLUDE = -I./include/ -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft

all: objs_folder $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f objs/*.o

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(BIN)$(NAME)

re: fclean all

objs_folder :
	@mkdir -p objs/

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_SRCS)
	@$(MAKE) -C $(LIBFT_DIR) all

$(NAME): $(SRCS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) ./srcs/minishell.c -o $(BIN)$(NAME)
	@echo "Minishell compiled successfully"

print_srcs:
	@echo $(SRCS)

.PHONY: all clean fclean re
