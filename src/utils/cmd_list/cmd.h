/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/11 18:55:18 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# include <stdlib.h>

typedef	struct			s_cmd
{
	unsigned char		type;
	char				*line;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

t_cmd		*cmd__ft_lstlast(t_cmd *lst);
t_cmd		*cmd__ft_lstnew(unsigned char type, char *line);
void		cmd__ft_lstdelone(t_cmd *lst, void (*del)(void*));
void		cmd__ft_lstclear(t_cmd **lst, void (*del)(void*));
void		cmd__ft_lstadd_front(t_cmd **alst, t_cmd *new);
void		cmd__ft_lstadd_back(t_cmd **alst, t_cmd *new);
int			cmd__ft_lstsize(t_cmd *lst);
void		cmd__ft_printlist(t_cmd *cmd);

#endif
