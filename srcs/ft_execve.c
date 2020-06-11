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
	//if(envp)
	//	return (NULL);
	while (i < size && list)
	{
		str = ft_strjoin("=", list->content);
		//if (!str)
		//	return (NULL);
		envp[i] = ft_strjoin(list->name, str); // MANY LEAKS
		// if (!envp[i])
		//	return (NULL);
		list = list->next;
		free(str);
		i++;
	}
	return (envp);
}

static char **__linkedlist_to_array(t_vars *v)
{
	size_t size;
	char **envp;

	envp = NULL;
	size = env__ft_lstsize(v->env_head);
	envp = __make_array(v, size, v->env_head);
	// if (!envp)
	// 	return (NULL)
	return (envp);
}

int ft_execve(t_vars *v, char *path, char **params)
{
	char **envp;
	int stat;

	envp = __linkedlist_to_array(v);
	pid_t spoon = fork();

	if (!spoon)
	{
		if (execve(path, &params[0], envp) < 0)
		{
			ft_printf("Error - %d\n", errno);
			// free envp
			exit(EXIT_FAILURE);
		}
	}
	wait(&stat);
	// free envp
	if (WEXITSTATUS(stat) == EXIT_FAILURE)
		return (0);
	return (1);
}