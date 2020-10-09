/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 08:42:59 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/09 10:36:10 by lverdoes      ########   odam.nl         */
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

static int		print_declare_list(char **array)
{
	size_t i;

	ascii_sort(array);
	i = 0;
	while (array[i] != NULL)
	{
		write(1, array[i], ft_strlen(array[i]));
		write(1, "\n", 1);
		i++;	
	}
	ft_free_array((void **)array, i);
	return (1);
}

static char		**create_declare_list(t_vars *v, size_t len)
{
	t_list	*tmp;
	t_env	*node;
	size_t	i;
	char	**array;

	i = 0;
	array = ft_calloc(len + 1, sizeof(char *));
	if (!array)
		ft_exit_error(v, EXIT_FAILURE);
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
		{
			ft_free_array((void **)array, i);
			ft_exit_error(v, EXIT_FAILURE);
		}
		i++;
		tmp = tmp->next;
	}
	return (array);
}

int		export_declare_list(t_vars *v)
{
	t_list	*tmp;
	t_env	*node;
	size_t	len;
	char	**array;
	
	len = ft_lstsize(v->env);
	printf("LEN = [%lu]\n", len); //debug?
	array = create_declare_list(v, len);
	if (!array)
		ft_exit_error(v, EXIT_FAILURE);
	return (print_declare_list(array));
}
