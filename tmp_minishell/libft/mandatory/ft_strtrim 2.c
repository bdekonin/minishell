/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 11:34:06 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/11 10:27:54 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

static size_t	set_check(char c, char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

static char		*trim_str(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*trim;

	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] != '\0')
	{
		if (set_check(s1[i], set))
			break ;
		i++;
	}
	while (j > i)
	{
		if (set_check(s1[j], set))
			break ;
		j--;
	}
	len = j - i + 1;
	trim = ft_substr(s1, i, len);
	return (trim);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	return (trim_str(s1, set));
}
