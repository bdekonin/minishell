# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lverdoes <lverdoes@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/09 18:45:34 by lverdoes      #+#    #+#                  #
#    Updated: 2020/12/08 18:44:05 by bdekonin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = \
	/main.c \
	/create_tokens.c \
	/execve.c \
	/expansion.c \
	/initialize.c \
	/syntax_error_check.c \
	/syntax_error_return.c \
	/multiline_check.c  \
	/run_pipe.c \
	/redirection_handler.c \
	/run_redirection.c \
	/handle_relative.c \
	/handle_static.c \
	/handle_static_more.c \
	/signal.c \
	/changestruct.c \
	/read_command_line_input.c \
	/read_command_line_input_more.c \
	/utils/pipeutils.c \
	/utils/cmd_utils.c \
	/utils/env_list_to_array.c \
	/utils/expansion_utils.c \
	/utils/expansion_utils_more.c \
	/utils/expansion_utils_more_more.c \
	/utils/ft_split_sep_exep_bonus.c \
	/utils/ft_split_sep_exep_utils.c \
	/utils/malloc_check.c \
	/utils/ft_iserrno_bonus.c \
	/utils/ft_reduce_spaces.c \
	/utils/find_env.c \
	/utils/is_functions.c \
	/utils/create_token_utils.c \
	/utils/linked_list_utils.c \
	/utils/reset_std.c \
	/utils/error_identifier.c \
	/builtins/ft_cd.c \
	/builtins/ft_echo.c \
	/builtins/ft_env.c \
	/builtins/ft_exit.c \
	/builtins/ft_export_utils.c \
	/builtins/ft_export.c \
	/builtins/ft_pwd.c \
	/builtins/ft_unset.c \
	/utils/cmd_list/ft_cmdadd_back_bonus.c \
	/utils/cmd_list/ft_cmdadd_front_bonus.c \
	/utils/cmd_list/ft_cmdclear_bonus.c \
	/utils/cmd_list/ft_cmddelone_bonus.c \
	/utils/cmd_list/ft_cmdlast_bonus.c \
	/utils/cmd_list/ft_cmdnew_bonus.c \
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
CC = gcc -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
INCLUDES = ./src/$(NAME).h

all: $(NAME)

./libft/libft.a:
	make -C ./libft

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) -o $(NAME) $(LIBFT) $(OBJ)

obj/%.o: src/%.c
	@mkdir -p obj obj/builtins/ obj/utils obj/utils/cmd_list obj/utils/env_list
	$(CC) -c $< -o $@

.PHONY: clean fclean re

clean:
	@/bin/rm -f $(OBJ)
	@make clean -C ./libft

fclean: clean
	@/bin/rm -f $(LIBFT) $(NAME)
	@/bin/rm -rf obj
	@make fclean -C ./libft

re: fclean all
