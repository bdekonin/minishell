/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/16 23:53:20 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int	free_array_three(char ***array)
{
	free(array);
	return (0);
}

static size_t	count_vars(char **params)
{
	size_t i;

	i = 0;
	while (params[i] && ft_strncmp(params[i], ";", 3))
	{
		i++;
	}
	return (i);
}

static int	trim_strings(char **s1, char **s2, char **src)
{
	char set[3];

	set[0] = 34;
	set[1] = 39;
	set[2] = 0;
	*s1 = ft_strtrim(src[0], set);
	if (!*s1)
	{
		ft_free_array((void*)src, 2);
		return (0);
	}
	*s2 = ft_strtrim(src[1], set);
	if (!*s2)
	{
		free(*s1);
		ft_free_array((void*)src, 2);
		return (0);
	}
	ft_free_array((void*)src, 2);
	return (1);
}
int 			export(t_vars *v, char **params)
{
	char	***sen;
	size_t	size;
	size_t	i;
	char	*dst_name;
	char	*dst_content;

	size = count_vars(&params[1]);
	sen = ft_calloc(size + 1, sizeof(char **));
	if (!sen)
		return (0); //malloc
	i = 0;
	while (i < size)
	{
		sen[i] = ft_split_lars(params[i + 1], '='); //rename to ft_split
		if (!sen[i])
			return (free_array_three(sen)); //malloc
		if (!trim_strings(&dst_name, &dst_content, sen[i]))
			return (free_array_three(sen)); //malloc
		env__ft_lstadd_back(&v->env_head, env__ft_lstnew(dst_name, dst_content));
		env__ft_lstmove_back("_", v->env_head);
		i++;
	}
	free(sen);
	return (1);
}