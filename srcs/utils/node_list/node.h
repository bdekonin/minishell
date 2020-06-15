/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/15 17:17:25 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

#include <stdlib.h>

typedef	struct			s_node
{
	unsigned char		type;
	int					i;
	char				*line;
	struct s_node		*next;
}						t_node;


/*
**		type			size			argv
**		;				3				{cd ..},{pwd}
**
** cd ..  | echo | pwd ; env && env ; env}
**
** cd ..  | echo | pwd 
** {cd ..}  {echo} {pwd}
** env
** env
*/

// cd .. || echo
// pwd

t_node		*node__ft_lstlast(t_node *lst);
t_node		*node__ft_lstnew(unsigned char type, int i, void *line);
void		node__ft_lstdelone(t_node *lst, void (*del)(void*));
void		node__ft_lstadd_back(t_node **alst, t_node *new);
void		node__ft_lstadd_front(t_node **alst, t_node *new);
void		node__ft_lstclear(t_node **lst, void (*del)(void*));
int			node__ft_lstsize(t_node *lst);


#endif
