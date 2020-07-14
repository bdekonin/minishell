# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bdekonin <bdekonin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 12:24:22 by bdekonin      #+#    #+#                  #
#    Updated: 2020/07/14 15:38:13 by bdekonin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = *.c srcs/builtins/*.c \
	srcs/utils/*.c srcs/utils/env_list/*.c \
	srcs/utils/history_list/*.c \
		srcs/utils/node_list/*.c \
		srcs/ft_execve/*.c 

OFILES = $(SRCS:.c=.o)

LIBFT = libft/libft.a

FT_PRINTF = ft_printf/libftprintf.a

CC = gcc -Wall -Wextra -Werror 

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -g $(SRCS) $(LIBFT) $(FT_PRINTF) -o $(NAME)

1:
	mv main.c main

2:
	mv main main.c

fclean:
	/bin/rm -f $(OFILES)
	/bin/rm -f $(NAME)
	/bin/rm -f minishell
	/bin/rm -r *.dSYM

re: fclean all
