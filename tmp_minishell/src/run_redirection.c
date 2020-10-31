/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_redirection.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 11:44:41 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/31 17:51:57 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

static int	read_file(t_vars *v, char *name, char **dest)
{
	int fd;
	int ret;
	
	fd = open(name, O_RDONLY);
	if (fd > -1)
	{
		ret = ft_getline(fd, dest);
		close(fd);
		if (ret < 0)
			ft_exit_error(v, EXIT_FAILURE);
		return (1);
	}
	return (0);
}

static int run_angle_right_double(t_vars *v, char **filename)
{
	char	*file_contents;
	ssize_t	ret;
	int		read_fd;
	
	expansion(v, filename);
	file_contents = NULL;
	ret = read_file(v, *filename, &file_contents);
	v->stdout_copy = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	v->fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (v->fd < 0)
		return (ft_free_ret_int(file_contents, 0)); //some error with target file
	if (ret)
	{	
		ret = write(1, file_contents, ft_strlen(file_contents));
		if (ret < 0 || (size_t)ret != ft_strlen(file_contents))
				return (ft_free_ret_int(file_contents, 0)); //write ereror
	}
	dup2(v->fd, STDOUT_FILENO);
	return (1);
}

static int run_angle_right_single(t_vars *v, char **filename)
{
	v->stdout_copy = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	v->fd = open(*filename, O_WRONLY | O_CREAT  | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (v->fd < 0)
		return (0);
	dup2(v->fd, STDOUT_FILENO);
	return (1);
}

static int run_angle_left_single(t_vars *v, char **filename)
{
	expansion(v, filename);
	v->fd = open(*filename, O_RDONLY);
	if (v->fd < 0)
	{
		close(v->fd);
		ft_printerror(*filename, ENOENT);
		return (0);
	}
	v->stdin_copy = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	dup2(v->fd, STDIN_FILENO);
	close(v->fd);
	return (1);
}

int mainredir(t_vars *v, char *flag, char *filename)
{
	int ret;

	if (!ft_strncmp(flag, ">>", 3))
		ret = run_angle_right_double(v, &filename);
	else if (!ft_strncmp(flag, ">", 2))
		ret = run_angle_right_single(v, &filename);
	else if (!ft_strncmp(flag, "<", 2))
		ret = run_angle_left_single(v, &filename);
	else
		ret = 0;
	if (!ret)
		return (0);
	return (ret);
}
t_list *lastpipe(t_list *headptr);
int redirection_handler(t_vars *v, t_list *list)
{	
	if (list->next == NULL)
		exit(EXIT_FAILURE);
	
	if (is_redirection(list->next->content))
		dprintf(2, "next flag = [%s]\n\n", list->content);
	
	dprintf(2, "list->content = [%s]\n", list->content);
	dprintf(2, "list->next->next = [%s]\n", list->next->content);
	dprintf(2, "lastpipe(list)->content = [%s]\n\n", lastpipe(list)->content);
	return (1);
}
