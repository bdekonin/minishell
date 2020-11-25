# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lverdoes <lverdoes@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/09 18:45:34 by lverdoes      #+#    #+#                  #
#    Updated: 2020/11/25 15:37:04 by lverdoes      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = \
	/create_tokens.c \
	/execve.c \
	/expansion.c \
	/initialize.c \
	/main.c \
	/syntax_error_check.c \
	/syntax_error_return.c \
	/run_pipe.c \
	/run_redirection.c \
	/handle_relative.c \
	/handle_static.c \
	/signal.c \
	/changestruct.c \
	/utils/pipeutils.c \
	/utils/cmd_utils.c \
	/utils/env_list_to_array.c \
	/utils/expansion_utils.c \
	/utils/ft_split_sep_exep_bonus.c \
	/utils/malloc_check.c \
	/utils/ft_iserrno_bonus.c \
	/utils/ft_reduce_spaces.c \
	/utils/find_env.c \
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
	/utils/cmd_list/ft_cmdsize_bonus.c \
	/utils/cmd_list/ft_cmd_removemiddle.c \
	/utils/env_list/ft_envadd_back_bonus.c \
	/utils/env_list/ft_envadd_front_bonus.c \
	/utils/env_list/ft_envclear_bonus.c \
	/utils/env_list/ft_envdelone_bonus.c \
	/utils/env_list/ft_envlast_bonus.c \
	/utils/env_list/ft_envmove_back_bonus.c \
	/utils/env_list/ft_envnew_bonus.c \
	/utils/env_list/ft_envremove_middle_bonus.c \
	/utils/env_list/ft_envsize_bonus.c

OBJ = $(addprefix obj, $(SRC:.c=.o))
CC = gcc -Wall -Wextra -Werror -g
LIBFT = ./libft/libft.a
PRINTF = ./ft_printf/libftprintf.a
INCLUDES = ./src/$(NAME).h

all: $(NAME)
	@./$(NAME)

./libft/libft.a:
	make -C ./libft

./ft_printf/libftprintf.a:
	make -C ./ft_printf

$(NAME): $(LIBFT) $(PRINTF) $(OBJ)
	@$(CC) -o $(NAME) $(LIBFT) $(PRINTF) $(OBJ)

obj/%.o: src/%.c
	@mkdir -p obj obj/builtins/ obj/utils obj/utils/cmd_list obj/utils/env_list
	$(CC) -c $< -o $@

.PHONY: clean fclean re

norm:
	@norminette $(SRC) $(INCLUDES) Makefile
	@make norm -C ./libft
	@make norm -C ./ft_printf

clean:
	@/bin/rm -f $(OBJ)
	@make clean -C ./libft
	@make clean -C ./ft_printf

fclean: clean
	@/bin/rm -f $(LIBFT) $(NAME)
	@/bin/rm -rf obj
	@make fclean -C ./libft
	@make fclean -C ./ft_printf

re: fclean all
