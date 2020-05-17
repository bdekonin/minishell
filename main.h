/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/17 10:42:06 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include "get_next_line/get_next_line.h"
#include "ft_printf/printf.h
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

# define d_prefix "%s@codam %s > "
# define cmd_notfound "%s: command not found: %s\n"
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
	t_env			*env_head; // DO NOT CHANGE THE VALUE!

	char			*__executable;	// another struct maybe?
	char			*__logname;		// This too?
}					t_vars;

int		ft_printf(const char *format, ...);

void	removespace(t_vars *v, char **argv); // Deze zou weg kunnen als cd is verbetert.
void	readline(t_vars *v);
char	**ft_split_lars(char const *s, char c);

void	cmd(t_vars *v, char **params);

// tijdelijke gevulde functies
int echo(t_vars *v, char **params);
int	cd(t_vars *v, char **params);
int pwd(t_vars *v, char **params);
int export(t_vars *v, char **params);
int unset(t_vars *v, char **params);
int env(t_vars *v, char **params);
int exitt(t_vars *v, char **params);
int help(t_vars *v, char **params);

// moeten we aanpassen, desnoods met de functie asprintf
char	*ft_strjoin_trip(char const *s1, char const *s2, char const *s3);

// env list functions
void	env__ft_lstadd_back(t_env **alst, t_env *new);
void	env__ft_lstadd_front(t_env **alst, t_env *new);
void	env__ft_lstclear(t_env **lst, void (*del)(void*));
void	env__ft_lstdelone(t_env *lst, void (*del)(void*));
t_env	*env__ft_lstlast(t_env *lst);
int		env__ft_lstsize(t_env *lst);
t_env	*env__ft_lstnew(void *name, void *content);
void	env__ft_lstmove_back(char *name, t_env *new);
void	env__ft_lstremove_middle(char *name, t_env *new);

#endif
