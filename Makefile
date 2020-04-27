# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bdekonin <bdekonin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 12:24:22 by bdekonin      #+#    #+#                  #
#    Updated: 2020/04/27 07:43:32 by bdekonin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = a.out

SRCS = *.c get_next_line/get_next_line.c

OFILES = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	gcc -Wall -Werror -Wextra $(SRCS) ft_printf/libftprintf.a

fclean:
	/bin/rm -f $(OFILES)
	/bin/rm -f $(NAME)
	/bin/rm -f a.out

re: fclean all
