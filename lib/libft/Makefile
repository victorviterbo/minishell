# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 12:45:22 by vviterbo          #+#    #+#              #
#    Updated: 2025/02/14 20:39:54 by vviterbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CHARACTERS			= 	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
						ft_isprint.c ft_tolower.c ft_toupper.c \
						ft_iswhitespace_eq.c
SRCS_CHARACTERS		=	$(addprefix characters/, $(CHARACTERS))
OBJS_CHARACTERS 	=	$(patsubst characters/%.c, objs/%.o, $(SRCS_CHARACTERS))

CONVERSIONS			=	ft_atof.c ft_atoi.c ft_ctoa.c ft_itoa.c ft_itoa_base.c \
						ft_utoa_base.c ft_number_len.c
SRCS_CONVERSIONS	=	$(addprefix conversions/, $(CONVERSIONS))
OBJS_CONVERSIONS 	=	$(patsubst conversions/%.c, objs/%.o, $(SRCS_CONVERSIONS))

LISTS				=	ft_lst_getn.c ft_lst_isin_int.c ft_lst_isin_void.c \
						ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
						ft_lstcut.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
						ft_lstmap_void.c ft_lstmax.c ft_lstmaxi.c ft_lstmin.c \
						ft_lstmini.c ft_lstnew_int.c ft_lstnew_void.c \
						ft_lstsize.c
SRCS_LISTS			=	$(addprefix lists/, $(LISTS))
OBJS_LISTS		 	=	$(patsubst lists/%.c, objs/%.o, $(SRCS_LISTS))

MATH				=	ft_abs.c ft_dotprod.c ft_initvec.c \
						ft_max.c ft_min.c ft_norm.c ft_prev_power.c \
						ft_vecadd.c ft_vecscale.c ft_vecsubstr.c
SRCS_MATH			=	$(addprefix math/, $(MATH))
OBJS_MATH		 	=	$(patsubst math/%.c, objs/%.o, $(SRCS_MATH))

MEMORY				=	ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c \
						ft_memcpy.c ft_memmove.c ft_memset.c
SRCS_MEMORY			=	$(addprefix memory/, $(MEMORY))
OBJS_MEMORY		 	=	$(patsubst memory/%.c, objs/%.o, $(SRCS_MEMORY))

MISCS				=	ft_arrlen.c ft_dummy.c ft_free_array.c ft_parse_as.c \
						ft_strarray_mapi.c ft_swap_void.c ft_array_append.c \
						ft_print_array.c
SRCS_MISCS			=	$(addprefix miscs/, $(MISCS))
OBJS_MISCS		 	=	$(patsubst miscs/%.c, objs/%.o, $(SRCS_MISCS))

STRINGS				=	ft_isfloat.c ft_isint.c ft_split.c ft_strchr.c \
						ft_strdup.c ft_striteri.c ft_strjoin.c ft_strjoin_ip.c \
						ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
						ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
						ft_substr.c ft_coalesce_char.c ft_strtrim_char.c \
						ft_count_charocc.c ft_count_strocc.c ft_str_replace.c \
						ft_strcmp.c
SRCS_STRINGS		=	$(addprefix strings/, $(STRINGS))
OBJS_STRINGS	 	=	$(patsubst strings/%.c, objs/%.o, $(SRCS_STRINGS))

TREE				=	ft_tree_clear.c ft_tree_new.c ft_tree_trav.c
SRCS_TREE			=	$(addprefix tree/, $(TREE))
OBJS_TREE		 	=	$(patsubst tree/%.c, objs/%.o, $(SRCS_TREE))

WRITE_READ			=	ft_get_next_line.c ft_putchar_fd.c \
						ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
						ft_readfile.c ft_printf.c
SRCS_WRITE_READ		=	$(addprefix write_read/, $(WRITE_READ))
OBJS_WRITE_READ 	=	$(patsubst write_read/%.c, objs/%.o, $(SRCS_WRITE_READ))

SRCS =	$(SRCS_CHARACTERS) $(SRCS_CONVERSIONS) $(SRCS_LISTS) $(SRCS_MATH) \
		$(SRCS_MEMORY) $(SRCS_MISCS) $(SRCS_STRINGS) $(SRCS_WRITE_READ)\
		$(SRCS_TREE)

OBJS =	$(OBJS_CHARACTERS) $(OBJS_CONVERSIONS) $(OBJS_LISTS) $(OBJS_MATH) \
        $(OBJS_MEMORY) $(OBJS_MISCS) $(OBJS_STRINGS) $(OBJS_WRITE_READ) \
        $(OBJS_TREE)

HEADER = libft.h

CFLAGS = -Wall -Wextra -Werror

CC = cc

INCLUDE = ./

all: $(NAME)

clean :
	@rm -f objs/*.o

fclean : clean
	@rm -f $(NAME)

re : fclean all

bonus : all

print_srcs:
	@echo $(SRCS)

objs_folder :
	@mkdir -p objs/

$(NAME): objs_folder $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "Libft compiled successfully"

objs/%.o: characters/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

objs/%.o: conversions/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

objs/%.o: math/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

objs/%.o: miscs/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

objs/%.o: strings/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

objs/%.o: write_read/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

objs/%.o: lists/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

objs/%.o: memory/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

objs/%.o: printf/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

objs/%.o: tree/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

.PHONY: all clean fclean re