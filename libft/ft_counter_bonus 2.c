/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_counter_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 18:34:51 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/10 20:52:12 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_counter(const char *s, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}
