/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 08:07:31 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/15 20:05:07 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include "get_next_line.h"

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
** Functions from ctype.h
*/
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isalnum(int c);

/*
** Function from string.h
*/
void				ft_bzero(void *s, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(char const *str);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle, \
size_t len);
char				*ft_strrchr(const char *str, int c);
char				*ft_strdup(const char *s1);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);

/*
** Functions from stdlib.h
*/
void				*ft_calloc(size_t count, size_t size);

/*
** Functions with memory
*/
void				*ft_memccpy(void *dst, const void *src, \
int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, \
const void *src, size_t n);
void				*ft_memset(void *str, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);

/*
** File Descriptor Functions
*/
int					ft_putchar_fd(char c, int fd);
int					ft_putendl_fd(char *s, int fd);
int					ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
** Handmade Functions
*/
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				**ft_split(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strtrim(char const *s1, char const *set);

/*
** Datatype Conversions
*/
char				*ft_itoa(int n);
int					ft_atoi(const char *str);

/*
** Project Bonus Functions
*/
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void*));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *), \
void (*del)(void *));

/*
** Other Projects
*/

/*
** Extra Bonus Functions
*/
int					ft_counter(const char *s, char c);
int					ft_strsearch(char *line, char *str);
int					ft_strsearch_bool(char *line, char *str);
int					ft_charsearch(char *str, char c);
int					ft_charsearch_bool(char *str, char c);
int					ft_intlen(long long n, int base);
int					ft_wordcount(char *str);
int					ft_abs(int x);
char				*ft_strcat(char *dst, const char *src);
void				ft_free_array(void **ptr, int size);
void				ft_swap(double *xp, double *yp);
void				ft_str_tolower(char *str);
char				**ft_split_sep(const char *src, char *sep, size_t *size);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_iserrno(int error);
int					ft_getline(int fd, char **line);
int					ft_strexpand(char **str, size_t size);

#endif
