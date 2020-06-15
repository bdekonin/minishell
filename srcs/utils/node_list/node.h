/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/15 10:46:53 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

#include <stdlib.h>

typedef	struct			s_node
{
	unsigned char	*type;
	size_t			*size;
	char			**argv;
	struct s_node	*next;
}						t_node;

/*
**		type			size			argv
**		;				3				{cd ..},{pwd}
**
** {cd ..  | echo | pwd ; env ; env}
*/


void	node__ft_lstdelone(t_node *lst, void (*del)(void*));
int	node__ft_lstsize(t_node *lst);
void	node__ft_lstadd_back(t_node **alst, t_node *new);
void	node__ft_lstadd_front(t_node **alst, t_node *new);
void	node__ft_lstclear(t_node **lst, void (*del)(void*));
t_node	*node__ft_lstlast(t_node *lst);
t_node	*node__ft_lstnew(void *type, void *size, void **argv);
int	node__ft_lstsize(t_node *lst);


#endif