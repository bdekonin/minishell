/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 16:38:16 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/16 12:03:13 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# include <stddef.h>

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr
					(const char *haystack, const char *needle, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap
					(t_list *lst, void *(*f)(void *), void (*del)(void *));

char				*ft_append(char *s1, const char *s2);
size_t				ft_array_size(const char **array);
char				**ft_arraydup(const char **array);
double				ft_atod(const char *str);
int					ft_charsearch(const char c, const char *set);
size_t				ft_counter(const char *s, const char *set);
int					ft_free_array(void **array, size_t i);
int					ft_free_ret_int(void *ptr, int ret);
void				*ft_free_ret_ptr(void *ptr, void *ret);
int					ft_free(void *ptr);
int					ft_getline(int fd, char **line);
int					ft_iswhitespace(int c);
void				ft_print_array(char **array);
char				**ft_realloc(char **src, const char *line, size_t *size);
char				**ft_split_multi(const char *src, char *sep, size_t *size);
void				ft_str_to_lower(char *str);
void				ft_str_to_upper(char *str);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_replace
					(char *s1, const char *s2, char *ptr, size_t ptr_len);
char				*ft_strxjoin(const char *src, ...);
size_t				ft_substrlen(const char *str, const char *set);
int					get_next_line(int fd, char **line);

void				ft_lstremove_one
					(t_list **head, t_list *node, void (*del)(void *));
void				ft_lstmove_back(t_list **head, t_list *node);
void				ft_lstmove_front(t_list **head, t_list *node);
void				ft_swap(char **a, char **b);
size_t				ft_wordcount(const char *s, char c);

#endif
