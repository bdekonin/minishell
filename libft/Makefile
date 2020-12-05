# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lverdoes <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/22 17:32:04 by lverdoes      #+#    #+#                  #
#    Updated: 2020/12/05 09:17:31 by lverdoes      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =	libft.a

MANDATORY =	\
	/mandatory/ft_memset.c \
	/mandatory/ft_bzero.c \
	/mandatory/ft_memcpy.c \
	/mandatory/ft_memccpy.c \
	/mandatory/ft_memmove.c \
	/mandatory/ft_memchr.c \
	/mandatory/ft_memcmp.c \
	/mandatory/ft_strlen.c \
	/mandatory/ft_strlcpy.c \
	/mandatory/ft_strlcat.c \
	/mandatory/ft_strchr.c \
	/mandatory/ft_strrchr.c \
	/mandatory/ft_strnstr.c \
	/mandatory/ft_strncmp.c \
	/mandatory/ft_atoi.c \
	/mandatory/ft_isalpha.c \
	/mandatory/ft_isdigit.c \
	/mandatory/ft_isalnum.c \
	/mandatory/ft_isascii.c \
	/mandatory/ft_isprint.c \
	/mandatory/ft_toupper.c \
	/mandatory/ft_tolower.c \
	/mandatory/ft_calloc.c \
	/mandatory/ft_strdup.c \
	/mandatory/ft_substr.c \
	/mandatory/ft_strjoin.c \
	/mandatory/ft_strtrim.c \
	/mandatory/ft_split.c \
	/mandatory/ft_itoa.c \
	/mandatory/ft_strmapi.c \
	/mandatory/ft_putchar_fd.c \
	/mandatory/ft_putstr_fd.c \
	/mandatory/ft_putendl_fd.c \
	/mandatory/ft_putnbr_fd.c

BONUS =	\
	/bonus/ft_lstnew_bonus.c \
	/bonus/ft_lstadd_front_bonus.c \
	/bonus/ft_lstsize_bonus.c \
	/bonus/ft_lstlast_bonus.c \
	/bonus/ft_lstadd_back_bonus.c \
	/bonus/ft_lstdelone_bonus.c \
	/bonus/ft_lstclear_bonus.c \
	/bonus/ft_lstiter_bonus.c \
	/bonus/ft_lstmap_bonus.c

ADDED =	\
	/added/ft_append_bonus.c \
	/added/ft_array_size_bonus.c \
	/added/ft_arraydup_bonus.c \
	/added/ft_atod_bonus.c \
	/added/ft_charsearch_bonus.c \
	/added/ft_counter_bonus.c \
	/added/ft_free_array_bonus.c \
	/added/ft_getline_bonus.c \
	/added/ft_iswhitespace_bonus.c \
	/added/ft_lstmove_back_bonus.c \
	/added/ft_lstmove_front_bonus.c \
	/added/ft_lstremove_one_bonus.c \
	/added/ft_print_array_bonus.c \
	/added/ft_realloc_bonus.c \
	/added/ft_replace_bonus.c \
	/added/ft_split_multi_bonus.c \
	/added/ft_str_to_lower_bonus.c \
	/added/ft_str_to_upper_bonus.c \
	/added/ft_strcmp_bonus.c \
	/added/ft_strxjoin_bonus.c \
	/added/ft_substrlen_bonus.c \
	/added/get_next_line_bonus.c \
	/added/ft_swap_bonus.c \
	/added/ft_wordcount_bonus.c

OBJ = $(addprefix obj, $(MANDATORY:.c=.o) $(BONUS:.c=.o) $(ADDED:.c=.o))

CC = gcc -Wall -Wextra -Werror

HEADERS = libft.h

IGNORE = .gitignore

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $?

obj/%.o: %.c
	@mkdir -p obj obj/mandatory obj/bonus obj/added
	$(CC) -c $< -o $@

norm:
	@norminette $(addprefix ., $(MANDATORY) $(BONUS) $(ADDED))
	@norminette $(HEADERS) Makefile

ignore:
	@echo $(NAME) > $(IGNORE)
	@echo .DS_Store >> $(IGNORE)
	@echo *.o >> $(IGNORE)
	@echo **/obj >> $(IGNORE)
	@echo a.out  >> $(IGNORE)
	@echo main.c >> $(IGNORE)
	@echo *.txt >> $(IGNORE)

.PHONY:	clean fclean re

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -f *~
	@/bin/rm -f *.o
	@/bin/rm -f .DS_Store
	@/bin/rm -f a.out

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f *.a

re: fclean all
