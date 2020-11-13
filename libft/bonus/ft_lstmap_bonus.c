/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 17:01:02 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/11 10:26:05 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tmp;

	if (!lst)
		return (0);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (0);
	lst = lst->next;
	while (lst)
	{
		tmp = ft_lstlast(new_list);
		tmp->next = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&new_list, del);
			return (0);
		}
		lst = lst->next;
	}
	return (new_list);
}
