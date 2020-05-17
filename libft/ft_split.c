/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 16:18:24 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/23 11:49:52 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*freee(char **arr, int y)
{
	while (y > 0)
	{
		y--;
		free(arr[y]);
	}
	free(arr);
	return (NULL);
}

/*
** counts characters of the word
*/

static int	checkstring(char *s, char c, int i)
{
	int a;

	a = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		a++;
	}
	return (a);
}

/*
** x = Length of the string where the index is now located.
** y = array counter.
*/

static char	**splitting(char const *s, char c, int i, char **arr)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y != ft_wordcount((char*)s))
	{
		if (s[i] != c)
		{
			x = checkstring((char*)s, c, i);
			arr[y] = ft_substr((char*)s, i, x);
			if (!arr[y])
				freee(arr, y);
			i = i + x;
			y++;
		}
		i++;
	}
	arr[y] = NULL;
	return (arr);
}

/*
** i =  index. its the counter of the string.
*/

char		**ft_split(char const *s, char c)
{
	int		i;
	char	**arr;

	i = 0;
	if (!s)
		return (NULL);
	arr = (char**)malloc(sizeof(char*) * (ft_wordcount((char*)s) + 1));
	if (arr == NULL)
		return (NULL);
	arr = splitting((char*)s, c, i, arr);
	return (arr);
}
