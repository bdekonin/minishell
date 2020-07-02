/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/01 22:47:10 by bdekonin      ########   odam.nl         */
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
	t_node			*nodehead;

	char			*prefix;
	char			*current_path;
	char			*line;
	int				ret;

	char			*__executable;	// another struct maybe?
	// char			*__homedir;		//this aswell lars.
	// char			*__oldpwd; // location of old pwd
	char			*__parentpid; // pid of parent program
	char			*__currentpid; // pid of parent program
	// char			*__$path;

	t_env			*__path; // keeps the node * even if the pointer of the variable changes.
	t_env			*__logname;
	t_env			*__homedir;
	t_env			*__oldpwd;
}					t_vars;

int				ft_printf(const char *fmt, ...);
int				ft_dprintf(int fd, const char *fmt, ...);
int				ft_vdprintf(int fd, const char *fmt, va_list argp);

char *parse_cd(t_vars *v, char *line);
// void	read_user_input(t_vars *v);

// int	run_command(t_vars *v, char **params);

// tijdelijke gevulde functies
int echo(t_vars *v, t_cmd *cmd, char **params, char **ret);
int	cd(t_vars *v, t_cmd *cmd, char **params, char **ret);
int pwd(t_vars *v, t_cmd *cmd, char **params, char **ret);
int exportt(t_vars *v, t_cmd *cmd, char **params, char **ret);
int unset(t_vars *v, t_cmd *cmd, char **params, char **ret);
int env(t_vars *v, t_cmd *cmd, char **params, char **ret);
int exitt(t_vars *v, t_cmd *cmd, char **params, char **ret);
int debug(t_vars *v, t_cmd *cmd, char **params, char **ret);

int					ft_execve(t_vars *v, t_node *node, char **params, char **ret);

char *find_environment_variable(t_vars *v, char *line);

int findflag(char *str, char *flags); // returns i of first flag found

#endif
