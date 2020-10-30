/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 18:52:10 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/10/30 15:19:13 by bdekonin      ########   odam.nl         */
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

# include <stdio.h>



// bash-3.2$ ./kanker
// ebash: ./kanker: No such file or directory
// bash-3.2$ echo $?
// 127

// Execve
# define FILEERROR -1
# define FILENOTFOUND 127
# define FILEFOUND 1
# define FILEPERMISSIONS 126

# define MINISHELL_ENOENT "No such file or directory"
# define MINISHELL_EACCES "Permission denied"

# define ENVIRONMENT_VAR_MISSING "'%s' is undefined. default: '%s'\n"
# define SYNTAX_ERROR "%s: syntax error near unexpected token `%s'\n"
# define INVALID_IDENTIFIER "%s: export: `%s': not a valid identifier\n"
# define PROMPT "minishell-1.0$ "

typedef	struct	s_env
{
	char		*name;
	char		*content;
}				t_env;

typedef struct  s_vars{
	int			fd;
	t_list		*env;
	t_list		*cmd;				//linked list of all tokens
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

/*
**				src/
*/

void			initialize(t_vars *v, char **envp);
int				syntax_error_check(t_vars *v, const char *cli);
void			create_tokens(t_vars *v, const char *cli);
void			find_semicolons(t_vars *v);
void			split_tokens(t_vars *v, char *string);
int				run_command(t_vars *v, char **params);
int				get_relative_path(t_vars *v, char **new_path, char **tokens);
int				loop_locations(t_vars *v, char **new_path, char **params);
int				ft_execve(t_vars *v, char **params);
void			expansion(t_vars *v, char **arg);
int	        	copy_envvar(t_vars *v, char *dst, char *src, size_t *i, size_t *j);

// int				run_pipe(t_vars *v, char *args, t_list *list);
int				run_redirection(t_vars *v, t_list *first_cmd, t_list *flag);

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
int 			is_end(char *str);
int				reset_std(t_vars *v);

char   	 		**env_list_to_array(t_vars *v);
char			*cmd_str(int i);

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