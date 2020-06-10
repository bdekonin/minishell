/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/10 07:40:46 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include "get_next_line/get_next_line.h"
#include "./libft/libft.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include "srcs/utils/history_list/history.h"
#include "srcs/utils/env_list/env.h"

# define d_prefix "%s@%s -> "
# define cmd_notfound "%s: command not found: %s\n"
# define bultins 8
# define dquote "dquote> "

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
	t_history		*history_head; // DO NOT CHANGE THE VALUE!

	char			**envp;

	char			*__executable;	// another struct maybe?
	char			*__logname;		// This too?
	char			*__homedir;		//this aswell lars.
	char			*__oldpwd; // location of old pwd


	int				has_env_changed; // is 1 when the the env has been changed. and 0 if not.

	int				i;

	int				flag_i;
	void			*argument_ret;

	char *temp; // for if oldpwd exist and path can be bigger
}					t_vars;

int				ft_printf(const char *fmt, ...);
int				ft_dprintf(int fd, const char *fmt, ...);
int				ft_vdprintf(int fd, const char *fmt, va_list argp);

char *removespace(t_vars *v, char *line);
void	read_user_input(t_vars *v);
char	**ft_split_lars(char const *s, char c, int *lst_size);

int	run_command(t_vars *v, char **params);

// tijdelijke gevulde functies
int echo(t_vars *v, char **params);
int	cd(t_vars *v, char **params);
int pwd(t_vars *v, char **params);
int exportt(t_vars *v, char **params);
int unset(t_vars *v, char **params);
int env(t_vars *v, char **params);
int exitt(t_vars *v, char **params);
int debug(t_vars *v, char **params);

int ft_execve(t_vars *v, char *file, char **params);





char *find_environment_variable(t_vars *v, char *line);

#endif
