/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/04/30 18:23:33 by bdekonin      ########   odam.nl         */
=======
/*   Updated: 2020/04/28 17:15:13 by bdekonin      ########   odam.nl         */
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include "get_next_line/get_next_line.h"
#include "ft_printf/libft/libft.h"
#include <stdio.h>
#include <dirent.h>

# define d_prefix "custom@codam %s > "
# define cmd_notfound "zsh: command not found: "
# define path_max 1024
# define bultins 8
# define strjoin_filler 94

typedef struct		s_vars
{
	char			*ptr;
	char			*prefix;
	char			*current_path;
	char			*line;
	int				ret;
	char			**argv;
	pid_t			forky;
<<<<<<< HEAD
	int				seperator;
	
	char *test;
=======
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1
}					t_vars;

int					ft_printf(const char *format, ...);

void removespace(t_vars *v, char **argv);
void	readline(t_vars *v);

int				cd(t_vars *v, char **params);


// TEMP FUNCTIONS
int echo(t_vars *v, char **params);
int pwd(t_vars *v, char **params);
int export(t_vars *v, char **params);
int unset(t_vars *v, char **params);
int env(t_vars *v, char **params);
int exitt(t_vars *v, char **params);
int help(t_vars *v, char **params);

void cmd(t_vars *v, char **params);


#endif
