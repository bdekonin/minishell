/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_swap_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:53:46 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/14 15:50:38 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_swap(char **str1, char **str2)
{
	char *temp;
	
	temp = *str1; 
	*str1 = *str2; 
	*str2 = temp;
	
}