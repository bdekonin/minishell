# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bdekonin <bdekonin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 12:24:22 by bdekonin      #+#    #+#                  #
#    Updated: 2020/06/16 12:15:03 by bdekonin      ########   odam.nl          #
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
	$(MAKE) -C libft
	$(MAKE) -C ft_printf
	gcc -Wall -Wextra $(SRCS) $(LIBFT) $(FT_PRINTF) -o $(NAME)

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C ft_printf clean

fclean:
	$(MAKE) -C libft fclean
	$(MAKE) -C ft_printf fclean
	/bin/rm -f $(OFILES)
	/bin/rm -f $(NAME)
	/bin/rm -f minishell

re: fclean all
