/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temp_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/02 12:05:01 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int export(t_vars *v, char **params)
{
	char	*ptr;
	size_t	len;
	char	*var_name;

	ptr = ft_strchr(params[1], '=') + 1;
	if (!ptr)
		return (0); //if not '=', error.
	len = ptr - params[1] - 1;
	var_name = ft_substr(params[1], 0, len);
	v->export_str = ft_strdup(ptr);
	



	// debug checks
	printf("var_name = [%s]\n", var_name);
	printf("v->e_str = [%s]\n", v->export_str);

	return (1);
}

