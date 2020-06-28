# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bdekonin <bdekonin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 12:24:22 by bdekonin      #+#    #+#                  #
#    Updated: 2020/06/26 08:07:59 by bdekonin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = *.c srcs/builtins/*.c \
	srcs/*.c srcs/utils/*.c srcs/utils/env_list/*.c \
	srcs/utils/history_list/*.c \
		srcs/utils/node_list/*.c

OFILES = $(SRCS:.c=.o)

LIBFT = libft/libft.a

FT_PRINTF = ft_printf/libftprintf.a

CC = gcc -Wall -Wextra -Werror 

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -g $(SRCS) $(LIBFT) $(FT_PRINTF) -o $(NAME)

fclean:
	/bin/rm -f $(OFILES)
	/bin/rm -f $(NAME)
	/bin/rm -f minishell

re: fclean all
