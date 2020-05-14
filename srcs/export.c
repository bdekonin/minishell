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

static void		print_array(char **arr, size_t max)
{
	// function for debugging
	size_t i;
	
	i = 0;
	while (i < max)
	{
		printf("nr.%lu = [%s]\t\t", i, arr[i]);
		i++;
	}
	printf("\n");
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

static int		trim_strings(char **s1, char **s2, char **vars)
{
	char set[3];

	set[0] = 34;
	set[1] = 39;
	set[2] = 0;
	
	*s1 = ft_strtrim(vars[0], set);
	*s2 = ft_strtrim(vars[1], set);
	free(vars[0]);
	free(vars[1]);
	free(vars);
	if (!*s1 || !*s2)
		return (0);
	return (1);
}

int 			export(t_vars *v, char **params)
{
	t_exp	e;
	char	**vars;
	size_t	i;

	e = v->exp_vars;
	e.size = count_vars(&params[1]);
	e.var_name = ft_calloc(e.size + 1, sizeof(char *));
	e.var_content = ft_calloc(e.size + 1, sizeof(char *));
	if (!e.var_name || !e.var_content)
		return (0); //malloc
	i = 0;
	while (i < e.size)
	{
		vars = ft_split_lars(params[i + 1], '='); //rename to ft_split
		if (!vars)
		{
			free(e.var_name);
			free(e.var_content);
			return (0); //malloc
		}
		if (!trim_strings(&e.var_name[i], &e.var_content[i], vars))
			return (0); //malloc
		i++;
	}
	//functions for debugging export:
	//print_array(e.var_name, e.size);
	//print_array(e.var_content, e.size);
	return (1);
}

