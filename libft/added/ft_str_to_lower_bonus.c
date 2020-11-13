/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_to_lower_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 12:40:37 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/21 12:40:53 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_str_to_lower(char *str)
{
	size_t i;

	if (!str)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}
