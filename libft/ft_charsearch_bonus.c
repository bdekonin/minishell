/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_charsearch_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/16 23:43:02 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/16 23:44:39 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_charsearch(char *str, int c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}