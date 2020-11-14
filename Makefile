# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lverdoes <lverdoes@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/09 18:45:34 by lverdoes      #+#    #+#                  #
#    Updated: 2020/11/14 14:52:34 by bdekonin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = \
	/create_tokens.c \
	/execve.c \
	/expansion.c \
	/find_semicolons.c \
	/initialize.c \
	/main.c \
	/syntax_error_check.c \
	/run_pipe.c \
	/run_redirection.c \
	/handle_relative.c \
	/handle_static.c \
	/signal.c \
	/changestruct.c \
	/utils/pipeutils.c \
	/utils/debug_functions.c \
	/utils/cmd_utils.c \
	/utils/env_list_to_array.c \
	/utils/expansion_utils.c \
	/utils/ft_split_sep_exep_bonus.c \
	/utils/malloc_check.c \
	/utils/ft_iserrno_bonus.c \
	/utils/ft_reduce_spaces.c \
	/utils/find_env_var.c \
	/utils/is_functions.c \
	/utils/linked_list_utils.c \
	/utils/reset_std.c \
	/builtins/ft_cd.c \
	/builtins/ft_echo.c \
	/builtins/ft_env.c \
	/builtins/ft_exit.c \
	/builtins/ft_export_utils.c \
	/builtins/ft_export.c \
	/builtins/ft_pwd.c \
	/builtins/ft_unset.c \
	/utils/cmd_list/ft_cmd_print_list.c \
	/utils/cmd_list/ft_cmdadd_back_bonus.c \
	/utils/cmd_list/ft_cmdadd_front_bonus.c \
	/utils/cmd_list/ft_cmdclear_bonus.c \
	/utils/cmd_list/ft_cmddelone_bonus.c \
	/utils/cmd_list/ft_cmdlast_bonus.c \
	/utils/cmd_list/ft_cmdnew_bonus.c \
	/utils/cmd_list/ft_cmdsize_bonus.c
	
OBJ = $(addprefix obj, $(SRC:.c=.o))

CC = gcc -Wall -Wextra -Werror -g

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
	@mkdir -p obj obj/builtins/ obj/utils obj/utils/cmd_list
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
