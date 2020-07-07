/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execve.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 14:50:11 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/07 23:15:52 by bdekonin      ########   odam.nl         */
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
** https://stackoverflow.com/questions/2605130/redirecting-exec-output-to-a-buffer-or-file
**
**
**
*/

int set_errno(void)
{
	if (errno == EACCES)
	{
		ft_printf("%s\n", strerror(errno));
		errno = 0;
		return (0);
	}
	if (errno == ENAMETOOLONG)
	{
		ft_printf("%s\n", strerror(errno));
		errno = 0;
		return (0);
	}
	if (errno == ENOENT)
	{
		ft_printf("%s\n", strerror(errno));
		errno = 0;
		return (0);
	}
	if (errno == ENOTDIR)
	{
		ft_printf("%s\n", strerror(errno));
		errno = 0;
		return (0);
	}
	if (errno == ENOMEM)
		return (-1);
	return (0);
}

int listFiles(const char *path, const char *command)
{
	struct dirent *dp;
	DIR *dir = opendir(path);

	// Unable to open directory stream
	if (!dir) 
		return (-1);

	while ((dp = readdir(dir)) != NULL)
	{
		if (!ft_strcmp(dp->d_name, command))
		{
			closedir(dir);
			return (1);
		}
	}

	// Close directory stream
	closedir(dir);
	return (0);
}

static char *make_command(char *path, char *command)
{
	size_t length;
	char *newpath;

	length = ft_strlen(path) + 1 + ft_strlen(command) + 1;
	newpath = ft_calloc(length, sizeof(char));
	if (!newpath)
		return (NULL);
	ft_strcat(newpath, path);
	ft_strcat(newpath, "/");
	ft_strcat(newpath, command);
	return (newpath);
}

static int find_executable(t_vars *v, char **newpath, char *command)
{
	char	**argv_dirs;
	size_t	size;
	int		j;
	int		ret;

	j = 0;
	argv_dirs = ft_split_sep(v->__path->content, ":", &size);
	if (!argv_dirs)
		return (-1);
	while (j < (int)size)
	{
		ret = listFiles(argv_dirs[j], command);
		if (ret == 1)
		{
			*newpath = make_command(argv_dirs[j], command);
			ft_free_array((void*)argv_dirs, size);
			if (!*newpath)
				return (-1);
			return (1);
		}
		if (ret < 0)
		{
			ft_free_array((void*)argv_dirs, size);
			return (set_errno());
		}
		j++;
	}
	ft_free_array((void*)argv_dirs, size);
	return (0);
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

int					ft_execve(t_vars *v, t_cmd *cmd, char **params, char **ret)
{
	char *path = NULL;
	int ii;
	
	ii = find_executable(v, &path, params[0]);
	
	if (ii < 0)
		return (-1);
	else if (ii == 1)
		ft_printf("Correctly!, path = %s\n", path);
	else if (ii == 0)
		ft_printf("Argoument not found :((\n");
	free(path);
		// ft_exit_error(v, 0); // TEMP
		exit(1);
	
	// envp = NULL;
	// envp = __linkedlist_to_array(v, envp, v->env_head); // return or parameter not both bitch
	// if (!envp)
	// 	return (0);
	// if (!look_in_locations(v, 0, params[0], &path)) // leaks
	// {
	// 	ft_free_array((void*)envp, env__ft_lstsize(v->env_head) + 1);
	// 	return (0);
	// }
	// spoon = fork();
	// if (!spoon)
	// {
	// 	if (execve(path, &params[0], envp) < 0)
	// 	{
	// 		ft_printf("Error - %d\n", errno);
	// 		ft_free_array((void*)envp, env__ft_lstsize(v->env_head));
	// 		exit(EXIT_FAILURE);
	// 	}
	// }
	// wait(&stat);
	// ft_free_array((void*)envp, env__ft_lstsize(v->env_head) + 1);
	// free(path);
	// if (WTERMSIG(stat) != SIGTSTP && WEXITSTATUS(stat) == EXIT_FAILURE)
	// 	return (0);
	*ret = ft_strdup("1");
	if (!*ret)
		return (0);
	return (1);
	(void)(cmd);
}
