/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_wordcount_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/23 11:06:47 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/23 12:42:30 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wordcount(char *str)
{
	int		count;

	if (!str)
		return (0);
	count = 0;
	while (*str)
	{
		while (*str && (*str == ' ' || *str == '\n' || *str == '\t'))
			str++;
		if (*str && *str != ' ' && *str != '\n' && *str != '\t')
		{
			count++;
			while (*str && *str != ' ' && *str != '\n' && *str != '\t')
				str++;
		}
	}
	return (count);
}
