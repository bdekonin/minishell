/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 18:52:10 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/12 21:13:39 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//




#include "../libft/libft.h"
#include <stdlib.h>		//EXIT_FAILURE EXIT_SUCCESS
#include <limits.h>		//PATH_MAX
#include <unistd.h>		//STDIN_FILENO
#include <errno.h>		//ERRNO, ENOMEM
#include <string.h>		//str_error
# include "utils/cmd_list/cmd.h"

# include <stdio.h>

/*
** Execve https://www.gnu.org/software/bash/manual/html_node/Exit-Status.html
*/
# define FILEERROR -1
# define FILENOTFOUND 127
# define FILEFOUND 1
# define FILEPERMISSIONS 126

# define CMDERR -1
# define ENOENT 2
# define EACCES 13

# define NUMARG 998
# define ARGCOUNT 999

# define MINISHELL_ENOENT "No such file or directory"
# define MINISHELL_EACCES "Permission denied"
# define MINISHELL_CMDERR "command not found"
# define MINISHELL_NUMARG "numeric argument required"
# define MINISHELL_ARGCOUNT "too many arguments"

# define ENVIRONMENT_VAR_MISSING "'%s' is undefined. default: '%s'\n"
# define SYNTAX_ERROR "%s: syntax error near unexpected token `%s'\n"
# define INVALID_IDENTIFIER "%s: export: `%s': not a valid identifier\n"
# define PROMPT "minishell-1.0$ "
# define MINISHELL "minishell"

# define PIPELINE 124 // |
# define ANGLEBRACKETLEFT 60 // <
# define ANGLEBRACKETRIGHT 62 // >
# define ANGLEBRACKETDOUBLERIGHT 63 // >>

typedef	struct	s_env
{
	char		*name;
	char		*content;
}				t_env;

typedef struct  s_vars{
	int			fd;
	t_list		*env;
	t_list		*tempcmd;
	t_cmd		*cmd;				//linked list of all tokens
	t_list		**semicolon_ptrs;	//pointers to the first token after a `;'
	char		*prefix;
	char		*current_path;
	int			cmd_ret;
	int			stdout_copy;
	int			stdin_copy;
	int			pipefd[2];
	pid_t		forky;
	pid_t		spoon;
	t_env		*default_path;
	t_env		*default_homedir;
	t_env		*default_oldpwd;
}               t_vars;

/*
**				libraries
*/

int				ft_printf(const char *fmt, ...);





int addarguments(t_list *list, int i);
int argumentremover(t_vars *v, t_list *list);

/*
**				src/
*/

void			initialize(t_vars *v, char **envp);
int				syntax_error_check(t_vars *v, const char *cli);
void			create_tokens(t_vars *v, const char *cli);
void			find_semicolons(t_vars *v);
void			split_tokens(t_vars *v, char *string);
int				run_command(t_vars *v, char **params);
int				ft_execve(t_vars *v, char **params);
void			expansion(t_vars *v, char **arg);
int	        	copy_envvar(t_vars *v, char *dst, char *src, size_t *i, size_t *j);


// Execve
int				handle_relative(t_vars *v, char **newpath, char *command);
int				handle_static(t_vars *v, char **newpath, char *command);
int				validate_file(char *filepath);


int redirection_handler(t_vars *v, t_cmd *command);

/*
**				src/builtins
*/

int				ft_cd(t_vars *v, char **params);
int				ft_pwd(t_vars *v, char **params);
int 			ft_echo(t_vars *v, char **params);
int				ft_exit(t_vars *v, char **params);
void			ft_exit_error(t_vars *v, int status, int print);
int 			ft_export(t_vars *v, char **params);
int 			ft_unset(t_vars *v, char **params);
int				ft_env(t_vars *v, char **params);

/*
**				src/utils
*/

void			create_new_env_var(t_vars *v, char *name, char *content);
void			create_new_token(t_vars *v, const char *ptr, size_t len);
t_list			*get_prev_node(t_vars *v, t_list *dst);
void			ft_lst_remove_one(t_list **head, t_list *node);
size_t			find_identifier_len(char *str);
char			*find_env_var(t_vars *v, char *identifier, size_t *len);
void			print_prefix(t_vars *v);
int				export_declare_list(t_vars *v);

int				ft_iserrno(int error);
char 			*ft_reduce_spaces(const char *str);

int				is_redirection(char *str);
int				is_pipe(char *str);
int				is_semicolon(char *str);
int				is_now_or_prev(t_vars *v, t_list *list);
int				reset_std(t_vars *v);

char   	 		**env_list_to_array(t_vars *v);
char			*cmd_str(int i);



// t_list *lastpipe(t_list *headptr);
t_cmd *lastpipe(t_cmd *headptr);
t_cmd *lastredir(t_cmd *headptr);


/*
** Signals
*/
void			signal_execve(int signal);
void			signal_default(int signal);

void ft_printerror(char *file, int error);

/*
**				debug functions - remove from .h, .c, and Makefile when finished
*/

void			print_tokens(t_vars *v, const char *title);

#endif