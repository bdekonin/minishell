/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execve.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 14:50:11 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/22 22:40:53 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

/*
** main.c
** chmod:                 420
** regular file
**
** minishell && kaas
** chmod:                 493
** regular file
**
**
**
**
*/

static int look_in_locations(t_vars *v, int i, char *command, char **path) // make sure it also checks it types of file
{
	DIR					*d;
	struct dirent		*dir;
	struct stat			sb;
	char 				**locs;
	size_t				size;

	locs = ft_split(v->__path->content, ':');
	if (!locs)
	{
		return (0);
	}
	while (locs[i])
	{
		d = opendir(locs[i]);
		while ((dir = readdir(d)) != NULL)
		{
			// printf("dir = %s\n", dir->d_name);
			if (!ft_strncmp(command, dir->d_name, 1024))
			{
				lstat(dir->d_name, &sb);
				int statchmod = sb.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
				closedir(d);
				*path = ft_calloc(ft_strlen(locs[i]) + ft_strlen(command) + 2, sizeof(char));
				*path = ft_strcat(*path, locs[i]);
				*path = ft_strcat(*path, "/");
				*path = ft_strcat(*path, command);
				ft_free_array((void*)locs, ft_counter(v->__path->content, ':') + 1);
				return (1);
			}
		}
		closedir(d);
		i++;
	}
	ft_free_array((void*)locs, ft_counter(v->__path->content, ':') + 1);
	return (0);
	// // ft_printf("path = [%s]\n", v->__path->content);
}

/*
** Converts the linked list environ to a array of strings. Terminated by NULL.
**
** @param  t_vars v		vars
** @param  char **envp	array which will be filled.
** @param  t_end *head	Pointer to first argument of environ linked list.
**
** @return char **		envp (filled)
*/

static char			**__linkedlist_to_array(t_vars *v, char **envp, t_env *head)
{
	int			i;
	size_t		size;
	size_t		length;

	i = 0;
	size = env__ft_lstsize(v->env_head);
	envp = ft_calloc(size + 1, sizeof(char*));
	if (!envp)
		return (NULL);
	while (head)
	{
		length = ft_strlen(head->name) + 2 + ft_strlen(head->content);
		envp[i] = ft_calloc(length, sizeof(char));
		if (!envp[i])
		{
			ft_free_array((void*)envp, i - 1);
			return (NULL);
		}
		ft_strcat(envp[i], head->name);
		ft_strcat(envp[i], "=");
		ft_strcat(envp[i], head->content);
		head = head->next;
		i++;
	}
	return (envp);
}

/*
** Executes binary/executable based on arguments
**
** @param  t_vars v			vars
** @param  char *path		path of executable e.g. -> "/usr/bin/leaks"
** @param  char **params	parameters of input e.g. ↓ (Has to be NULL terminated)
**													{leaks},
**													{minishell},
**													{NULL}
**
** @return char **			envp (filled)
*/

int					ft_execve(t_vars *v, t_node *node, char **params, char **ret)
{
	char *path;
	char **envp;
	int stat;
	pid_t spoon;

	envp = NULL;
	envp = __linkedlist_to_array(v, envp, v->env_head);
	if (!envp)
		return (0);
	if (!look_in_locations(v, 0, params[0], &path)) // leaks
	{
		ft_free_array((void*)envp, env__ft_lstsize(v->env_head) + 1);
		return (0);
	}
	spoon = fork();
	if (!spoon)
	{
		if (execve(path, &params[0], envp) < 0)
		{
			ft_printf("Error - %d\n", errno);
			ft_free_array((void*)envp, env__ft_lstsize(v->env_head));
			exit(EXIT_FAILURE);
		}
	}
	wait(&stat);
	ft_free_array((void*)envp, env__ft_lstsize(v->env_head) + 1);
	free(path);
	if (WTERMSIG(stat) != SIGTSTP && WEXITSTATUS(stat) == EXIT_FAILURE)
		return (0);
	*ret = ft_strdup("1");
	if (!*ret)
		return (0);
	return (1);
	(void)(node);
}
