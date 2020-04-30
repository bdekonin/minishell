/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 22:58:42 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/30 19:01:15 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <errno.h>

static void		updatepath(t_vars *v)
{
	v->current_path = getcwd(v->current_path, path_max);
}

// Version 2.0
int				cd(t_vars *v, char **params)
{
	if (ft_wordcount(v->line) > 2 && \
	params[1][ft_strlen(params[1]) - 1] == 92)
		removespace(v, params + 1);
	ft_printf("line = %s\n", v->test);
	for (int i = 0; i < ft_wordcount(v->line); i++)
	{
		ft_printf("str1 = [%s]\t[%s]\n", params[i], v->argv[i]);
	}
	if (!v->argv[1])
		chdir("/Users/bdekonin");
	else if (chdir(v->argv[1]) == -1)
		perror("ERROR\n");
	updatepath(v);
	return (1);
}

// REDO VERSION 1.0
// int				cd(t_vars *v, char **params)
// {
// 	v->ptr = NULL;
// 	if (ft_wordcount(v->line) > 2 && \
// 	params[1][ft_strlen(params[1]) - 1] == 92)
// 		removespace(v, params + 1);
// 	if (v->ptr && ft_wordcount(v->line) > 2)
// 	{
// 		movestring(v);
// 		if (v->ptr && chdir(v->ptr) == -1)
// 			perror("ERROR\n");
// 	}
// 	else
// 	{
// 		if (chdir(params[1]) == -1)
// 			perror("ERROR");
// 	}
// 	updatepath(v);
// 	if (params[2] && *(params[2]) == ';')
// 		cmd(v, params + 3);
// 	return (1);
// }