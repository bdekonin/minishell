/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_tolower_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 15:07:58 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/06 13:56:46 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_str_tolower(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}
