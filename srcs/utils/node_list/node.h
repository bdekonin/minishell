/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/01 15:30:56 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

#include <stdlib.h>

typedef	struct			s_cmd
{
	unsigned char		type;
	char				*line;
	struct s_cmd		*next;
}						t_cmd;

typedef	struct			s_node
{
	t_cmd				*cmd;
	struct s_node		*next;
}						t_node;

/*
**		type			size			argv
**		;				3				{cd ..},{pwd}
**
**		command1 | command2 | command3 > output-file
**
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
t_node		*node__ft_lstnew(t_cmd **cmd);
// void		node__ft_lstdelone(t_node *lst, void (*del)(void*));
void		node__ft_lstadd_back(t_node **alst, t_node *new);
void		node__ft_lstadd_front(t_node **alst, t_node *new);
void	node__ft_lstclear(t_node **lst, void (*del)(void*));
int			node__ft_lstsize(t_node *lst);

t_cmd	*cmd__ft_lstlast(t_cmd *lst);
t_cmd	*cmd__ft_lstnew(unsigned char type, char *line);
void	cmd__ft_lstdelone(t_cmd *lst, void (*del)(void*));
void	cmd__ft_lstclear(t_cmd **lst, void (*del)(void*));
void	cmd__ft_lstadd_front(t_cmd **alst, t_cmd *new);
void	cmd__ft_lstadd_back(t_cmd **alst, t_cmd *new);
int			cmd__ft_lstsize(t_cmd *lst);


#endif
