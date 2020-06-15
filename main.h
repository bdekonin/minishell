/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/14 19:38:45 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include "./libft/libft.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include "srcs/utils/node_list/node.h"
#include "srcs/utils/history_list/history.h"
#include "srcs/utils/env_list/env.h"

# define d_prefix "%s@%s -> "
# define cmd_notfound "%s: command not found: %s\n"
# define bultins 8
# define dquote "dquote> "

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

typedef struct		s_vars
{
	t_env			*env_head; // DO NOT CHANGE THE VALUE!
	t_history		*history_head; // DO NOT CHANGE THE VALUE!

	char			*prefix;
	char			*current_path;
	char			*line;
	int				ret;
	char			**argv;

	char			*__executable;	// another struct maybe?
	char			*__logname;		// This too?
	char			*__homedir;		//this aswell lars.
	char			*__oldpwd; // location of old pwd
	char			*__ppid;

	int				i;

	int				flag_i;
	void			*argument_ret;
}					t_vars;

int				ft_printf(const char *fmt, ...);
int				ft_dprintf(int fd, const char *fmt, ...);
int				ft_vdprintf(int fd, const char *fmt, va_list argp);

char *removespace(t_vars *v, char *line);
void	read_user_input(t_vars *v);
char	**ft_split_lars(char const *s, char c, int *lst_size);

// int	run_command(t_vars *v, char **params);

// tijdelijke gevulde functies
int echo(t_vars *v, char *line, char **params);
int	cd(t_vars *v, char *line, char **params);
int pwd(t_vars *v, char *line, char **params);
int exportt(t_vars *v, char *line, char **params);
int unset(t_vars *v, char *line, char **params);
int env(t_vars *v, char *line, char **params);
int exitt(t_vars *v, char *line, char **params);
int debug(t_vars *v, char *line, char **params);

int ft_execve(t_vars *v, char *file, char **params);

char *find_environment_variable(t_vars *v, char *line);

#endif
