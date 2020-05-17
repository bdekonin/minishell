/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/10 20:49:53 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/10 20:49:55 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** first it counts needle and if needle is uqual to 0 then it can return the,
** whole haystack again.
** then while the index of haystack and the index isnt equal to the len
** then it compares the the index to the index of needle.
** J is the amount of correct characters compared.
** once count (amount of characters of needle) is == to J
** then it returns it from that point
** else it returns NULL
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t count;

	i = 0;
	j = 0;
	count = ft_strlen(needle);
	if (count == 0)
		return ((char*)haystack);
	while (haystack[i] != '\0' && i != len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j != len)
		{
			j++;
			if (count == j)
				return ((char*)haystack + i);
		}
		i++;
	}
	return (0);
}
