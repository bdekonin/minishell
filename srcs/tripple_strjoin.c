/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tripple_strjoin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 22:47:53 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/15 22:48:48 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*ft_strjoin_trip(char const *s1, char const *s2, char const *s3)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy(str + ft_strlen(s1), s2, ft_strlen(s2));
	ft_memcpy(str + ft_strlen(s1) + ft_strlen(s2), s3, ft_strlen(s3));
	return (str);
}
