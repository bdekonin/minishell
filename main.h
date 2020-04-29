/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/28 23:06:07 by bdekonin      ########   odam.nl         */
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
# define strjoin_filler 32

typedef struct		s_vars
{
	char			*ptr;
	char			*prefix;
	char			*current_path;
	char			*line;
	int				ret;
	char			**argv;
	pid_t			forky;
}					t_vars;

int					ft_printf(const char *format, ...);

void removespace(t_vars *v, char **argv);
void	readline(t_vars *v);

#endif
