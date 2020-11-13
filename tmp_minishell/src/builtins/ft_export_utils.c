/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 08:42:59 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/01 21:14:48 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		swap(char **s1, char **s2)
{
	char *tmp;
	
	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

static void		ascii_sort(char **array)
{
	size_t len;
	size_t i;
	size_t j;

	len = 0;
	while (array[len] != NULL)
		len++;
	if (len < 2)
		return ;
	len--;
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			if (ft_strncmp(array[j], array[j + 1], ft_strlen(array[j] + 1)) > 0)
				swap(&array[j], &array[j + 1]);
			j++;
		}
		i++;
	}
}

static int		print_declare_list(t_vars *v, char **array, size_t len)
{
	size_t	i;
	ssize_t	ret;

	ascii_sort(array);
	i = 0;
	while (i < len)
	{
		ret = write(1, array[i], ft_strlen(array[i]));
		if (ret < 0 || (size_t)ret != ft_strlen(array[i]))
			ft_exit_error(v, EXIT_FAILURE, 1);
		if (write(1, "\n", 1) != 1)
			ft_exit_error(v, EXIT_FAILURE, 1);
		i++;	
	}
	ft_free_array((void **)array, i);
	return (0);
}

static void		create_declare_list(t_vars *v, char **array, size_t len)
{
	t_list	*tmp;
	t_env	*node;
	size_t	i;

	i = 0;
	tmp = v->env;
	while (i < len && tmp)
	{
		node = tmp->content;
		if (!node->content)
			array[i] = ft_strxjoin("declare -x ", node->name, NULL);
		else if (*(node->content) == '\0')
			array[i] = ft_strxjoin("declare -x ", node->name, "=\"", "\"", NULL);
		else
			array[i] = ft_strxjoin("declare -x ", node->name, "=\"", node->content, "\"", NULL);
		if (!array[i])
			ft_exit_error(v, EXIT_FAILURE, 1);
		i++;
		tmp = tmp->next;
	}
}

int		export_declare_list(t_vars *v)
{
	t_list	*tmp;
	t_env	*node;
	size_t	len;
	char	**array;
	
	len = ft_lstsize(v->env);
	array = ft_calloc(len + 1, sizeof(char *));
	if (!array)
		ft_exit_error(v, EXIT_FAILURE, 1);
	create_declare_list(v, array, len);
	return (print_declare_list(v, array, len));
}
