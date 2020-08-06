/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 11:34:38 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/15 21:42:59 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *tmp;

	tmp = malloc(sizeof(t_list));
	if (!tmp)
		return (0);
	tmp->content = content;
	tmp->next = NULL;
	return (tmp);
}
