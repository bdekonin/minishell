/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:19:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/22 17:13:17 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdio.h>
# include <stdlib.h>
# include "../../../libft/libft.h"

typedef	struct		s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

void				env__ft_lstadd_back(t_env **alst, t_env *new);
void				env__ft_lstadd_front(t_env **alst, t_env *new);
void				env__ft_lstclear(t_env **lst, void (*del)(void*));
void				env__ft_lstdelone(t_env *lst, void (*del)(void*));
int					env__ft_lstsize(t_env *lst);
void				env__ft_lstmove_back(char *name, t_env *new);
void				env__ft_lstremove_middle(char *name, t_env *new);
t_env				*env__ft_lstnew(void *name, void *content);
t_env				*env__ft_lstlast(t_env *lst);

#endif
