/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/16 19:16:50 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include "get_next_line/get_next_line.h"
#include "ft_printf/libft/libft.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

# define d_prefix "custom@codam %s > "
# define cmd_notfound "zsh: command not found: %s"
# define path_max 1024
# define bultins 8
# define strjoin_filler 94
# define error "ERROR"

typedef	struct		s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef	struct		s_exp
{
	size_t			size;
	char			**var_name;
	char			**var_content;
}					t_exp;

typedef struct		s_vars
{
	char			*ptr;
	char			*prefix;
	char			*current_path;
	char			*line;
	int				ret;
	char			**argv;
	pid_t			forky;
	int				argc;
	t_exp			exp_vars;

	t_env			*env__home_ptr; // DO NOT CHANGE THE VALUE!
}					t_vars;

int		ft_printf(const char *format, ...);

void	removespace(t_vars *v, char **argv);
void	readline(t_vars *v);
char	**ft_split_lars(char const *s, char c);

int		cd(t_vars *v, char **params);

int		amountofsplits(t_vars *v, char **params);

void	cmd(t_vars *v, char **params);

// TEMP FUNCTIONS
int echo(t_vars *v, char **params);
int pwd(t_vars *v, char **params);
int export(t_vars *v, char **params);
int unset(t_vars *v, char **params);
int env(t_vars *v, char **params);
int exitt(t_vars *v, char **params);
int help(t_vars *v, char **params);

// WILL CHANGE
char	*ft_strjoin_trip(char const *s1, char const *s2, char const *s3);


// env list functions
void	env__ft_lstadd_back(t_env **alst, t_env *new);
void	env__ft_lstadd_front(t_env **alst, t_env *new);
void	env__ft_lstclear(t_env **lst, void (*del)(void*));
void	env__ft_lstdelone(t_env *lst, void (*del)(void*));
t_env	*env__ft_lstlast(t_env *lst);
int		env__ft_lstsize(t_env *lst);
t_env	*env__ft_lstnew(void *name, void *content);




#endif
