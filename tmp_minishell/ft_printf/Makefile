# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lverdoes <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/11 15:22:52 by lverdoes      #+#    #+#                  #
#    Updated: 2020/10/09 23:38:01 by lverdoes      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC =	ft_printf.c printf_utils.c libft_utils.c init_flags.c format_int.c \
		format_int_2.c format_str.c format_char.c ft_itoa.c ft_uitohex.c \
		ft_uitoa.c ft_ptr.c

OBJ =	$(SRC:.c=.o)

INCLUDES = ft_printf.h

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDES)
	ar rcs $(NAME) $?

%.o: %.c
	gcc -Wall -Wextra -Werror -c $<

norm:
	norminette $(SRC) $(INCLUDES)

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -f *~

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
