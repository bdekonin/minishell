/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/23 19:57:29 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

#include "../../../main.h"

typedef	struct		s_history
{
	char				*line;
	char				*output;
	char				*command;
	struct s_history	*next;
}					t_history;

// his list functions

void	his__ft_lstadd_back(t_history **alst, t_history *new);
void	his__ft_lstadd_front(t_history **alst, t_history *new);
void	his__ft_lstclear(t_history **lst, void (*del)(void*));
void	his__ft_lstdelone(t_history *lst, void (*del)(void*));
t_history	*his__ft_lstlast(t_history *lst);
int		his__ft_lstsize(t_history *lst);
t_history	*his__ft_lstnew(void *command, void *output, void *line);

#endif
