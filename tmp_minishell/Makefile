# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lverdoes <lverdoes@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/07 09:40:23 by lverdoes      #+#    #+#                  #
#    Updated: 2020/09/30 12:31:43 by lverdoes      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = \
	/main.c \
	/initialize.c \
	/syntax_error_check.c \
	/create_tokens.c \
	/ft_exit.c \
	/check_multiline_input.c \
	/confirm_flags.c \
	/expansion.c \
	/find_flags.c \
	/find_environment_variable.c \
	/ft_run_pipe.c \
	/get_relative_path.c \
	/loop_locations.c \
	/env_list_to_array.c \
	/reset_stdin_stdout.c \
	/signal_handler.c \
	/utils/export_utils.c \
	/utils/cmd_utils.c \
	/utils/print_prefix.c \
	/utils/ft_split_sep_exep.c \
	/utils/ft_iserrno_bonus.c \
	/builtins/ft_cd.c \
	/builtins/ft_echo.c \
	/builtins/ft_env.c \
	/builtins/ft_export.c \
	/builtins/ft_unset.c \
	/builtins/ft_pwd.c

OBJ = $(addprefix obj, $(SRC:.c=.o))

CC = gcc -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

PRINTF = ./ft_printf/libftprintf.a

INCLUDES = ./src/$(NAME).h

UNUSED = -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function

all: $(NAME)
	@./$(NAME)

./libft/libft.a:
	make -C ./libft

./ft_printf/libftprintf.a:
	make -C ./ft_printf

$(NAME): $(LIBFT) $(PRINTF) $(OBJ)
	@$(CC) $(UNUSED) -o $(NAME) $(LIBFT) $(PRINTF) $(OBJ)

obj/%.o: src/%.c
	@mkdir -p obj obj/builtins/ obj/utils
	$(CC) $(UNUSED) -c $< -o $@

.PHONY: clean fclean re

norm:
	@norminette $(SRC) $(INCLUDES) Makefile
	@make norm -C ./libft
	@make norm -C ./ft_printf

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(LIBFT) $(NAME)
	@make fclean -C ./libft
	@make fclean -C ./ft_printf

re: fclean all

lib:
	@mkdir -p libft
	cp -R ~/documents/repositories/libft/Makefile ./libft
	cp -R ~/documents/repositories/libft/libft.h ./libft
	cp -R ~/documents/repositories/libft/mandatory ./libft
	cp -R ~/documents/repositories/libft/bonus ./libft
	cp -R ~/documents/repositories/libft/added ./libft
