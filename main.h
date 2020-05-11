/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/02 17:05:06 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include "get_next_line/get_next_line.h"
#include "ft_printf/libft/libft.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

# define d_prefix "custom@codam %s > "
# define cmd_notfound "zsh: command not found: %s"
# define path_max 1024
# define bultins 8
# define strjoin_filler 94
# define error "ERROR"

typedef	struct		s_export
{
	char			*var_name;
	char			*var_content;
}					t_export;


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
	char			*export_str;
}					t_vars;

int		ft_printf(const char *format, ...);

void	removespace(t_vars *v, char **argv);
void	readline(t_vars *v);

int		cd(t_vars *v, char **params);

int		amountofsplits(t_vars *v, char **params);

void	cmd(t_vars *v, char **params);

// TEMP FUNCTIONS
int echo(t_vars *v, char **params);
int pwd(t_vars *v, char **params);
int export(t_vars *v, char **params);
int unset(t_vars *v, char **params);
int env(t_vars *v, char **params);
int exitt(t_vars *v, char **params);
int help(t_vars *v, char **params);



#endif
