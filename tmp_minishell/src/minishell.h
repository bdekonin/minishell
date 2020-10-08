/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/07 09:40:28 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/08 15:09:34 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
# include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h> //for strerror
#include <sys/errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#define	EXIT_FAILURE 1
#define	EXIT_SUCCESS 0
#define FLAGS "<|>" //mandatory flags
#define PATH_MAX 1024
#define BUILTINS 9

# define DQUOTE "DQUOTE> "
# define PREFIX "%s@%s$ " /* WILL BE SHOWED BEFORE COMMAND INPUT */
# define CMD_NOTFOUND "%s: %s: command not found\n" /* IF COMMAND DOESNT EXIST*/
# define DIR_NOTFOUND "\x1B[31m%s: %s: no such file or directory\n\x1B[0m" /* IF DIRECTORY DOESNT EXIST*/
# define ENVIRONMENT_VAR_MISSING "'%s' is undefined. default: '%s'\n" /*, name, content*/
# define COMMAND_NOT_RUNNABLE 127 /* command not found / not runnable */
# define SYNTAX_ERROR "%s: syntax error near unexpected token `%c'\n"
# define MISSING_LOGNAME "user" // is logname env is missing
# define MISSING_SHELLNAME "minishell" //if SHELLname env is missing


typedef	struct	s_env
{
	char		*name;
	char		*content;
}				t_env;

typedef	struct	s_cmd
{
	int			is_flag;
	char		*token;
}				t_cmd;

typedef struct	s_vars
{
	int			fd;
	char		*prefix;
	char		*current_path;
	t_list		*env;
	t_list		*cmd;
	t_list		**cmd_ptr;
//	t_list		*his;	

	
	t_env		*default_path;
	t_env		*default_logname;
	t_env		*default_homedir;
	t_env		*default_oldpwd;
	t_env		*default_executable;
	
	int			cmd_ret;				//use for '$?'
	int			stdout_copy;
	int			stdin_copy;
	int			pipefd[2];
	pid_t		forky;
	pid_t		spoon;
	char		*temp;
	int			exit_status;			//doesnt seem to be used //maybe redo ft_exit
	size_t		index_flag;
}				t_vars;

int				ft_printf(const char *fmt, ...);

/*
**				src/
*/

int				initialize_struct(t_vars *v, char **envp);
int				syntax_error_check(t_vars *v, const char *cli);
int				create_tokens(t_vars *v, const char *cli);

int				expansions(t_vars *v, char **arg);
char 			*find_environment_variable(t_vars *v, char *var, size_t *len);
void   			check_multiline_input(t_vars *v, char **arg);
int			 	confirm_flags(t_vars *v, char **params, size_t size_params, int i);
int				run_flags_command(t_vars *v, t_list *tmp);
int				split_tokens(t_vars *v, char **args);
int				run_command(t_vars *v, char **param);
int				run_pipe(t_vars *v, t_list *tmp);
size_t  		find_flags(t_vars *v, char **arg);
int				get_relative_path(t_vars *v, char **new_path, char **tokens);
int				loop_locations(t_vars *v, char **new_path, char **params);
char    		**env_list_to_array(t_vars *v);
int				reset_std(t_vars *v);

/*
**				src/builtins
*/

int				ft_cd(t_vars *v, char **params);
int				ft_pwd(t_vars *v, char **params);
int 			ft_echo(t_vars *v, char **params);
int				ft_exit(t_vars *v, char **params);
void    		ft_exit_error(t_vars *v, int status);
int 			ft_export(t_vars *v, char **params);
int 			ft_unset(t_vars *v, char **params);
int				ft_env(t_vars *v, char **params);

/*
**				src/utils
*/

void			print_prefix(t_vars *v);
void			resize_str(t_vars *v, char **str1, char *str2);
int				export_declare_list(t_vars *v);
char			**ft_split_sep_exep(const char *src, char *sep, size_t *size);
int				ft_iserrno(int error);
void			ft_lst_remove_one_after(t_list **head, t_list *node);
void			ft_lst_remove_one(t_list **head, t_list *node);
t_list			*get_prev_node(t_vars *v, t_list *dst);
int				is_redirection(t_list *tmp);
int				is_pipe(char *arg);
int				is_semicolon(char *arg);
void			free_cmd_list(t_vars *v);
void			find_semicolons(t_vars *v);

/*
**				src/signal_handler
*/

void			sig_catcher(void);


//				debug funcs, remove if done

void			print_tokens(t_vars *v);

#endif
