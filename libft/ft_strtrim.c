/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/21 10:45:55 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/26 21:44:07 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		trim_left(char *s1, char *set)
{
	int i;
	int j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i] != set[j] && set[j])
			j++;
		if (!set[j])
			break ;
		i++;
	}
	return (i);
}

static int		trim_right(char *s1, char *set)
{
	int i;
	int j;

	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		j = 0;
		while (s1[i] != set[j] && set[j])
			j++;
		if (!set[j])
			break ;
		i--;
	}
	return (i);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		left;
	int		right;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	left = trim_left((char*)s1, (char*)set);
	right = trim_right((char*)s1, (char*)set);
	if (right - left + 1 < 0)
		return (ft_strdup(""));
	str = ft_substr(s1, left, right - left + 1);
	if (!str)
		return (NULL);
	return (str);
}
