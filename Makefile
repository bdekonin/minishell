# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bdekonin <bdekonin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 12:24:22 by bdekonin      #+#    #+#                  #
<<<<<<< HEAD
#    Updated: 2020/04/28 23:01:56 by bdekonin      ########   odam.nl          #
=======
#    Updated: 2020/04/28 16:42:51 by bdekonin      ########   odam.nl          #
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1
#                                                                              #
# **************************************************************************** #

NAME = a.out

SRCS = *.c get_next_line/get_next_line.c srcs/*.c

OFILES = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	gcc -Wall -Werror -Wextra $(SRCS) ft_printf/libftprintf.a

compile: $(NAME)
	rm a.out && make && ./a.out

fclean:
	/bin/rm -f $(OFILES)
	/bin/rm -f $(NAME)
	/bin/rm -f a.out

re: fclean all
