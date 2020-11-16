/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_replace_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/02 16:37:09 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/07 00:05:49 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**	s1:			The source string in which a part is to be replaced.
**	s2:			The new string which must be pasted into s1.
**				If s2 is NULL or empty ("\0"), nothing is pasted, but depending
**				on the length of ptr_len, a part can still be removed.
**	ptr:		The starting point of the part to be removed from s1.
**				If ptr is outside s1, NULL is returned.
**				If ptr points to the '\0' of s1, it will function like strjoin.
**	ptr_len:	The length of the part to be removed.
**				If ptr_len is 0, nothing is removed.
**				ptr_len is 'safe' if it is too big for s1.
**	return:		A modified copy of s1 is returned.
*/

static size_t	get_ptr_len(char *s1, char *ptr, size_t s1_len, size_t ptr_len)
{
	if (ptr_len > s1 - ptr + s1_len)
		return (s1 - ptr + s1_len);
	return (ptr_len);
}

static size_t	get_strlen(const char *s2)
{
	if (s2)
		return (ft_strlen(s2));
	return (0);
}

char			*ft_replace(char *s1, const char *s2, char *ptr, size_t ptr_len)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	len;
	char	*dst;

	if (!s1 || ptr < s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	if (s1 + s1_len < ptr)
		return (NULL);
	ptr_len = get_ptr_len(s1, ptr, s1_len, ptr_len);
	s2_len = get_strlen(s2);
	len = s1_len - ptr_len + s2_len;
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, ptr - s1 + 1);
	if (s2)
		ft_strlcat(dst, s2, len + 1);
	else
		ft_strlcat(dst, "", len + 1);
	ft_strlcat(dst, ptr + ptr_len, len + 1);
	return (dst);
}
