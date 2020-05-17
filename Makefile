# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bdekonin <bdekonin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 12:24:22 by bdekonin      #+#    #+#                  #
#    Updated: 2020/05/17 15:02:28 by lverdoes      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = a.out

SRCS = *.c get_next_line/get_next_line.c srcs/builtins/*.c \
	srcs/utils/*.c srcs/utils/env_list/*.c

OFILES = $(SRCS:.c=.o)

LIBFT = libft/libft.a

FT_PRINTF = ft_printf/libftprintf.a

CC = gcc -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra $(SRCS) $(LIBFT) $(FT_PRINTF)

c: $(NAME)
	rm a.out && make && ./a.out

fclean:
	/bin/rm -f $(OFILES)
	/bin/rm -f $(NAME)
	/bin/rm -f a.out

re: fclean all
