/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substrlen_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/02 17:21:35 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/11 10:24:59 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_substrlen(const char *str, const char *set)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	if (!set)
		return (ft_strlen(str));
	while (str[i] != '\0')
	{
		if (ft_charsearch(str[i], set))
			return (i);
		i++;
	}
	return (i);
}
