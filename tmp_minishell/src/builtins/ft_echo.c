/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 13:33:04 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/16 10:01:04 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*	Echo edgecases:
**
**	echo "" -n hoi"   "hoi"  " | cat -e
**	echo -n -n -n -n -n -n -n hoi
**	
*/

static size_t	check_newline_option(char **params, int *newline_opt)
{
	size_t i;

	i = 0;
	if (params[i] && !ft_strncmp(params[i], "-n", 3))
	{
		*newline_opt = 1;
		i++;
	}
	else
		*newline_opt = 0;
	while (params[i] && !ft_strncmp(params[i], "-n", 3))
		i++;
	return (i);
}

static char		*init_dst(char *param, size_t *i)
{
	char *dst;

	if (param)
	{
		dst = ft_strdup(param);
		*i += 1;
	}
	else
		dst = ft_strdup("\0");
	return (dst);
}

static int		append_to_dst(char **params, char **dst, size_t i)
{
	char *tmp;
	
	while (params[i])
	{
		tmp = ft_strxjoin(*dst, " ", params[i], NULL);
		free(*dst);
		if (!tmp)
			return (0);
		*dst = tmp;
		i++;
	}
	return (1);
}

int 			ft_echo(t_vars *v, char **params)
{
	ssize_t	ret;
	size_t	i;
	int		newline_opt;
	char	*dst;

	i = check_newline_option(params, &newline_opt);
	dst = init_dst(params[i], &i);
	if (!dst)
		return (0);
	if (!append_to_dst(params, &dst, i))
		return (0);
	ret = write(1, dst, ft_strlen(dst));
	free(dst);
	if (ret < 0 || (size_t)ret != ft_strlen(dst))
		return (0); //write error
	if (newline_opt == 0 && write(1, "\n", 1) != 1)
		return (0);
	//if (!sethistory(&v->history_head, v->line, "1"))
	//	return (0);
	(void)(params);
	//(void)(cmd);
	return (1);
}
