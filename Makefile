# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bdekonin <bdekonin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 12:24:22 by bdekonin      #+#    #+#                  #
#    Updated: 2020/04/28 16:42:51 by bdekonin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = a.out

SRCS = *.c get_next_line/get_next_line.c srcs/*.c

OFILES = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	gcc -Wall -Werror -Wextra $(SRCS) ft_printf/libftprintf.a

fclean:
	/bin/rm -f $(OFILES)
	/bin/rm -f $(NAME)
	/bin/rm -f a.out

re: fclean all
