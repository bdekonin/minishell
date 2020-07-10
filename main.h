/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/10 16:05:29 by bdekonin      ########   odam.nl         */
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
#include <signal.h>

#include "srcs/utils/node_list/node.h"
#include "srcs/utils/history_list/history.h"
#include "srcs/utils/env_list/env.h"

# define PREFIX "%s@%s$ " /* WILL BE SHOWED BEFORE COMMAND INPUT */
# define CMD_NOTFOUND "%s: %s: command not found\n" /* IF COMMAND DOESNT EXIST*/
# define DIR_NOTFOUND "\x1B[31m%s: %s: no such file or directory\n\x1B[0m" /* IF DIRECTORY DOESNT EXIST*/
# define bultins 8
# define dquote "dquote> "
# define PIPE 124
# define RDIRLEFT 60
# define RDIRRIGHT 62
# define FLAGS "<|>"
# define TRIMS " \t"
# define COMMAND_NOT_RUNNABLE 127 /* command not found / not runnable */

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
	t_env			*env_head; // malloc
	t_history		*history_head; // malloc
	t_node			*nodehead; // malloc

	t_cmd			**cmdlist;

	char			*prefix; // malloc
	char			*current_path; // malloc
	char			*line; // malloc
	int				ret;

	char			*__executable;	// another struct maybe?
	// char			*__homedir;		//this aswell lars.
	// char			*__oldpwd; // location of old pwd
	// char			*__parentpid; // pid of parent program
	// char			*__currentpid; // pid of parent program

	t_env			*__path; // keeps the node * even if the pointer of the variable changes.
	t_env			*__logname;
	t_env			*__homedir;
	t_env			*__oldpwd;
	int				exit_status;
}					t_vars;

int				ft_printf(const char *fmt, ...);

char *parse_cd(t_vars *v, char *line);

// tijdelijke gevulde functies
int echo(t_vars *v, t_cmd *cmd, char **params, char **ret);
int	cd(t_vars *v, t_cmd *cmd, char **params, char **ret);
int pwd(t_vars *v, t_cmd *cmd, char **params, char **ret);
int exportt(t_vars *v, t_cmd *cmd, char **params, char **ret);
int unset(t_vars *v, t_cmd *cmd, char **params, char **ret);
int env(t_vars *v, t_cmd *cmd, char **params, char **ret);
int ft_exit(t_vars *v, t_cmd *cmd, char **params, char **ret);
int debug(t_vars *v, t_cmd *cmd, char **params, char **ret);

int		ft_execve(t_vars *v, t_cmd *cmd, char **params, char **ret);
char	*find_environment_variable(t_vars *v, char *line);

int		findflag(char *str, char *flags); // returns i of first flag found

int		sethistory(t_history **his, char *fullcommand, char *ret);

void	ft_exit_error(t_vars *v, int status); // call this function to exit program if error or just return 1 anywhere

int find_executable(t_vars *v, char **newpath, char *command);
#endif
