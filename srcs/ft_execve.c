/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execve.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 14:50:11 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/18 11:36:49 by bdekonin      ########   odam.nl         */
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

static char *look_in_locations(t_vars *v, int i, char *command) // make sure it also checks it types of file
{
	DIR *d;
	struct dirent *dir;
	struct stat		sb;
	char **locs;

	locs = ft_split(v->__path->content, ':');
	if (!locs)
		return (NULL);
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

					ft_printf("chmod:                 %d\n", statchmod);

					switch (sb.st_mode & S_IFMT)
					{
						case S_IFBLK:  printf("block device\n");            break;
						case S_IFCHR:  printf("character device\n");        break;
						case S_IFDIR:  printf("directory\n");               break;
						case S_IFIFO:  printf("FIFO/pipe\n");               break;
						case S_IFLNK:  printf("symlink\n");                 break;
						case S_IFREG:  printf("regular file\n");            break;
						case 28672:	   printf("binary\n");            break;
						case S_IFSOCK: printf("socket\n");                  break;
						default:       printf("unknown?\n");                break;
					}

					// printf("I-node number:            %ld\n", (long) sb.st_ino);

					// printf("Mode:                     %lo (octal)\n",
					// 			(unsigned long) sb.st_mode);

					// printf("Link count:               %ld\n", (long) sb.st_nlink);
					// printf("Ownership:                UID=%ld   GID=%ld\n",
					// 			(long) sb.st_uid, (long) sb.st_gid);

					// printf("Preferred I/O block size: %ld bytes\n",
					// 			(long) sb.st_blksize);
					// printf("File size:                %lld bytes\n",
					// 			(long long) sb.st_size);
					// printf("Blocks allocated:         %lld\n",
					// 			(long long) sb.st_blocks);

					// printf("Last status change:       %s", ctime(&sb.st_ctime));
					// printf("Last file access:         %s", ctime(&sb.st_atime));
					// printf("Last file modification:   %s\n\n", ctime(&sb.st_mtime));
			
				closedir(d);
				return (ft_strjoin(locs[i], ft_strjoin("/", command)));
			}
		}
		closedir(d);
		i++;
	}
	return (NULL);
	// ft_printf("path = [%s]\n", v->__path->content);
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
		length = ft_strlen(head->name) + 1 + ft_strlen(head->content);
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

int					ft_execve(t_vars *v, t_node *node, char **params)
{
	char *path;
	char **envp;
	int stat;
	pid_t spoon;

	envp = NULL;
	envp = __linkedlist_to_array(v, envp, v->env_head);
	if (!envp)
		return (0);
	path = look_in_locations(v, 0, params[0]); // leaks
	if (!path)
		return (0);
	spoon = fork();
	ft_printf("path = %s\n", path);

	// for (int i = 0; params[i]; i++)
	// 	ft_printf("params = [%s]\n", params[i]);
	// fork protect
	
	if (!spoon)
	{
		if (execve(path, &params[0], envp) < 0)
		{
			ft_printf("Error - %d\n", errno);
			ft_free_array((void*)envp, env__ft_lstsize(v->env_head));
			exit(EXIT_FAILURE);
		}
	}
		ft_printf("HIeruit\n");
	wait(&stat);
	ft_free_array((void*)envp, env__ft_lstsize(v->env_head) + 1);
	if (WTERMSIG(stat) != SIGTSTP && WEXITSTATUS(stat) == EXIT_FAILURE)
	{
		return (0);
	}
	return (1);
	(void)(node);
}
