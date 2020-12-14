/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 18:52:10 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/12/08 18:46:04 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include "../libft/libft.h"
# include "utils/cmd_list/cmd.h"
# include "utils/env_list/env.h"

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

# define ENV_DELIMS ",.+-/%^:="
# define STRING_SPECIAL_CHAR "\b"
# define STRING_SPECIAL_CHAR2 "\b "
# define CHAR_SPECIAL_CHAR '\b'

# define MINISHELL_ENOENT "No such file or directory"
# define MINISHELL_EACCES "Permission denied"
# define MINISHELL_CMDERR "command not found"
# define MINISHELL_NUMARG "numeric argument required"
# define MINISHELL_ARGCOUNT "too many arguments"

# define SYNTAX_ERROR ": syntax error near unexpected token `"

# define PROMPT "minishell-1.0$ "
# define MINISHELL "minishell"

# define PIPELINE 124
# define ANGLEBRACKETLEFT 60
# define ANGLEBRACKETRIGHT 62
# define ANGLEBRACKETDOUBLERIGHT 63

typedef struct	s_exp{
	char		*dst;
	t_cmd		*tmp;
	char		**array;
	size_t		array_iter;
	size_t		array_size;
	char		sub_dst[PATH_MAX + 1];
	size_t		i;
	size_t		j;
}				t_exp;

typedef struct	s_vars{
	int			fd;
	t_env		*env;
	t_list		*tempcmd;
	t_cmd		*cmd;
	char		*current_path;
	int			cmd_ret;
	int			stdout_copy;
	int			stdin_copy;
	int			empty_quotes;
	char		*backup_command;
}				t_vars;

/*
**				src/
*/

void			initialize(t_vars *v, char **envp, char **cli);
int				initial_syntax_error_check(t_vars *v, const char *cli);
int				syntax_error_check_loop
				(t_vars *v, char **args, size_t splitsize);
int				syntax_error_check(t_vars *v, const char *cli);
int				syntax_error_return(t_vars *v, const char *token);
int				multiline_check(t_vars *v, const char *cli);
int				check_flag_syntax(t_vars *v, const char *cli, size_t i);
void			create_tokens(t_vars *v, const char *cli);
void			find_semicolons(t_vars *v);
void			split_tokens(t_vars *v, char *string);
int				run_command(t_vars *v, char **params, size_t i);
int				ft_execve
				(t_vars *v, char **params, char *path, char *backup_command);

/*
**				expansions
*/

void			expansion(t_vars *v);
int				copy_envvar(t_vars *v, t_exp *e);
void			copy_char(t_exp *e);
void			copy_space(t_exp *e);
void			copy_single_quote(t_vars *v, t_exp *e);
void			print_empty_token_space(t_vars *v, t_exp *e);
void			copy_backslash(t_exp *e);
void			copy_hashtag(t_exp *e);
void			copy_double_quote(t_vars *v, t_exp *e);

/*
**				input
*/

int				read_command_line_input(t_vars *v, char *cli);
void			ft_printerror(char *file, int error);
char			*make_backup_command(t_vars *v, char *backup);
void			control_d(t_vars *v, char **cli, int ret);
int				error_identifier(char *identifier);
int				free_input_args(void **array, size_t i);

/*
**				pipes
*/

int				pipe_handler(t_vars *v, t_cmd *temp);
int				pipe_stuff(t_vars *v, t_cmd *list);
int				redirection_handler(t_vars *v, t_cmd *command);
int				mainredir(t_vars *v, unsigned char type, char *filename);
t_cmd			*lastpipe(t_cmd *headptr);
t_cmd			*lastredir(t_cmd *headptr);

/*
**				Execve
*/

int				handle_relative(t_vars *v, char **newpath, char *command);
int				handle_static(t_vars *v, char **newpath, char *command);
int				validate_file(char *filepath);
int				loop_searchdir(struct dirent **dp, char *command, DIR *dir);
int				searchdir(char *location, char *command);

/*
**				src/builtins
*/

int				ft_cd(t_vars *v, char **params);
int				ft_pwd(t_vars *v, char **params);
int				ft_echo(t_vars *v, char **params);
int				ft_exit(t_vars *v, char **params);
void			ft_exit_error(t_vars *v, int status, int print);
int				ft_export(t_vars *v, char **params);
int				ft_unset(t_vars *v, char **params);
int				ft_env(t_vars *v, char **params);

/*
**				src/utils
*/

void			create_new_env_var
				(t_vars *v, char *name, char *content, int checkmalloc);
void			create_new_token(t_vars *v, const char *ptr, size_t len);
size_t			get_token_len(const char *cli, size_t start);
void			add_bogus_token(t_vars *v);
t_list			*get_prev_node(t_vars *v, t_list *dst);
void			ft_lst_remove_one(t_list **head, t_list *node);
size_t			find_identifier_len(char *str);
t_env			*find_env(t_vars *v, char *identifier, size_t *len);
int				export_declare_list(t_vars *v);
int				ft_iserrno(int error);
char			*ft_reduce_spaces(const char *str, size_t size, size_t i);
int				is_redirection_new(unsigned char type);
int				is_redirection(char *str);
int				is_pipe(char *str);
int				reset_std(t_vars *v);
char			**env_list_to_array(t_vars *v);
char			*cmd_str(int i);
char			**ft_split_sep_exep(const char *src, char *sep, size_t *size);
size_t			get_start_split(const char *src, char *sep, size_t i);
size_t			get_len_split(const char *src, char *sep, size_t start);
void			malloc_check(t_vars *v, void *ptr);
size_t			skip_quotations(const char *cli, char quotation_type);
void			changestruct(t_vars *v, t_cmd *list);

/*
** Signals
*/

void			signal_execve(int signal);
void			signal_default(int signal);

#endif
