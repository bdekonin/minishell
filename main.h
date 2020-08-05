/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/08/05 09:54:08 by lverdoes      ########   odam.nl         */
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

/*
** FLAGS
*/

# define PIPE 124 // |
# define ANGLEBRACKETLEFT 60 // <
# define ANGLEBRACKETRIGHT 62 // >
# define ANGLEBRACKETDOUBLERIGHT 63 // >>


# define PREFIX "%s@%s$ " /* WILL BE SHOWED BEFORE COMMAND INPUT */
# define CMD_NOTFOUND "%s: %s: command not found\n" /* IF COMMAND DOESNT EXIST*/
# define DIR_NOTFOUND "\x1B[31m%s: %s: no such file or directory\n\x1B[0m" /* IF DIRECTORY DOESNT EXIST*/
# define bultins 9
# define DQUOTE "DQUOTE> "
# define FLAGS "<|>" //mandatory flags
# define TRIMS " \t" // Command will be trimmed in spaces and tabs
# define ENVIRONMENT_VAR_MISSING "'%s' is undefined. default: '%s'\n" /*, name, content*/
# define COMMAND_NOT_RUNNABLE 127 /* command not found / not runnable */
# define SYNTAX_ERROR "%s: syntax error near unexpected token `%c'\n"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


# define MISSING_LOGNAME "user" // is logname env is missing
# define MISSING_SHELLNAME "minishell" //if SHELLname env is missing

typedef struct		s_vars
{
	t_env			*env_head; // malloc
	t_history		*history_head; // malloc
	t_node			*nodehead; // malloc
	int				fd;

	t_cmd			**cmdlist;

	char			*prefix; // malloc // user@minishell$ 
	char			*current_path; // malloc
	char			*line; // malloc for gnl
	int				ret; // gnl ret

	int				stdout_copy;
	
	
	int				stdin_copy;
	int pipefd[2];
	pid_t forky;
	pid_t spoon;

	char			*temp;


	t_env			*__path; //default
	t_env			*__logname; //default
	t_env			*__homedir; //default
	t_env			*__oldpwd; //default
	t_env			*__executable;
	int				exit_status; // existatus is 1 if error, used in ft_exit_error
}					t_vars;

int				ft_printf(const char *fmt, ...);

// tijdelijke gevulde functies
int echo(t_vars *v, t_cmd *cmd, char **params);
int	cd(t_vars *v, t_cmd *cmd, char **params);
int pwd(t_vars *v, t_cmd *cmd, char **params);
int exportt(t_vars *v, t_cmd *cmd, char **params);
int unset(t_vars *v, t_cmd *cmd, char **params);
int env(t_vars *v, t_cmd *cmd, char **params);
int ft_exit(t_vars *v, t_cmd *cmd, char **params);
int debug(t_vars *v, t_cmd *cmd, char **params);

int	ft_history(t_vars *v, t_cmd *cmd, char **params);

int		ft_execve(t_vars *v, t_cmd *cmd, char **params, size_t *splitsize);
char	*find_environment_variable(t_vars *v, char *line, size_t *len);

int		findflag(char *str, char *flags); // returns i of first flag found

int		sethistory(t_history **his, char *fullcommand, char *ret_str);

void	ft_exit_error(t_vars *v, int status); // call this function to exit program if error or just return 1 anywhere

int		find_executable(t_vars *v, char **newpath, char *command);


char	**ft_split_sep_exep(const char *src, char *sep, size_t *size);
int     expansions(t_vars *v, char **arg);
int		export_declare_list(t_env **head);
#endif
