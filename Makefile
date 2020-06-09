# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bdekonin <bdekonin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 12:24:22 by bdekonin      #+#    #+#                  #
#    Updated: 2020/06/09 16:22:50 by bdekonin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = *.c get_next_line/get_next_line.c srcs/builtins/*.c \
	srcs/*.c srcs/utils/*.c srcs/utils/env_list/*.c \
	srcs/utils/history_list/*.c

OFILES = $(SRCS:.c=.o)

LIBFT = libft/libft.a

FT_PRINTF = ft_printf/libftprintf.a

CC = gcc -Wall -Wextra -Werror 

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra $(SRCS) $(LIBFT) $(FT_PRINTF) -o  minishell

c: $(NAME)
	make re && ./minishell

fclean:
	/bin/rm -f $(OFILES)
	/bin/rm -f $(NAME)
	/bin/rm -f minishell

re: fclean all
