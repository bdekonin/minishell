/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execve.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekoin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 14:50:11 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/18 15:56:33 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static char **__make_array(t_vars *v, int size, t_env *list)
{
	int			i;
	char		**envp;
	char		*str;

	i = 0;
	size = env__ft_lstsize(v->env_head);
	envp = ft_calloc(size + 1, sizeof(char*)); // + 1 VOOR NULL
	while (i < size && list)
	{
		str = ft_strjoin("=", list->content);
		envp[i] = ft_strjoin(list->name, str); // MANY LEAKS
		list = list->next;
		free(str);
		i++;
	}
	return (envp);
}

static char **__linkedlist_to_array(t_vars *v, int *list_size)
{
	int i;
	char **envp;

	envp = NULL;
	i = 0;
	if (*list_size == 0)
	{
		*list_size = env__ft_lstsize(v->env_head);
		envp = __make_array(v, *list_size, v->env_head);
		return (envp);
	}
	ft_free_array((void*)v->envp, *list_size + 1);
	ft_printf("CHECCK");
	envp = __make_array(v, *list_size, v->env_head);
	*list_size = env__ft_lstsize(v->env_head);
	v->has_env_changed = 0;
	return (envp);
}

int ft_execve(t_vars *v, char *file, char **params)
{
	int stat;
	static int list_size;

	if (v->has_env_changed == 1 || list_size == 0)
		v->envp = __linkedlist_to_array(v, &list_size);
	pid_t spoon = fork();

	if (!spoon)
	{
		if (execve(file, &params[0], v->envp) < 0)
		{
			// ft_printf("INvalid thingy [%s]\n", params[0]);
			exit(EXIT_FAILURE);
		}
	}
	wait(&stat);
	if (WEXITSTATUS(stat) == EXIT_FAILURE)
		return (0);
	return (1);
}