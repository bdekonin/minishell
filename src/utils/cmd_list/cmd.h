/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/12/04 14:10:06 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <stdlib.h>

typedef	struct			s_cmd
{
	unsigned char		type;
	char				*line;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

t_cmd					*cmd__ft_lstlast(t_cmd *lst);
t_cmd					*cmd__ft_lstnew(unsigned char type, char *line);
void					cmd__ft_lstdelone(t_cmd *lst, void (*del)(void*));
void					cmd__ft_lstclear(t_cmd **lst, void (*del)(void*));
void					cmd__ft_lstadd_front(t_cmd **alst, t_cmd *new);
void					cmd__ft_lstadd_back(t_cmd **alst, t_cmd *new);
int						cmd__removemiddle(t_cmd *remove, int ret);

#endif
