/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_redirection.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 11:44:41 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/26 21:26:55 by bdekonin      ########   odam.nl         */
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
			ft_exit_error(v, EXIT_FAILURE, 1);
		return (1);
	}
	return (0);
}

static int run_angle_right_double(t_vars *v, char *filename)
{
	char	*file_contents;
	ssize_t	ret;

	file_contents = NULL;
	ret = read_file(v, filename, &file_contents);
	v->stdout_copy = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	v->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
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

static int run_angle_right_single(t_vars *v, char *filename)
{
	v->stdout_copy = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	v->fd = open(filename, O_WRONLY | O_CREAT  | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (v->fd < 0)
		return (0);
	dup2(v->fd, STDOUT_FILENO);
	return (1);
}

static int run_angle_left_single(t_vars *v, char *filename)
{
	v->fd = open(filename, O_RDONLY);
	if (v->fd < 0)
	{
		close(v->fd);
		ft_printerror(filename, ENOENT);
		return (0);
	}
	v->stdin_copy = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	dup2(v->fd, STDIN_FILENO);
	close(v->fd);
	return (1);
}

static int mainredir(t_vars *v, unsigned char type, char *filename)
{
	int ret;
	char **argv;

	argv = ft_split(filename, '*');
	malloc_check(v, argv);
	if (type == ANGLEBRACKETDOUBLERIGHT)
		ret = run_angle_right_double(v, argv[0]);
	else if (type == ANGLEBRACKETRIGHT)
		ret = run_angle_right_single(v, argv[0]);
	else if (type == ANGLEBRACKETLEFT)
		ret = run_angle_left_single(v, argv[0]);
	else
		ret = 0;
	ft_free_array((void**)argv, ft_array_size((const char**)argv));
	if (!ret)
		return (0);
	return (ret);
}

int redirection_handler(t_vars *v, t_cmd *list)
{
	if (list && list->type >= 60 && list->type != PIPELINE)
	{
		if (mainredir(v, list->type, list->next->line) == 0)
			return (0);
	}
	if (list && list->type == ANGLEBRACKETLEFT &&
	list->next && list->next->next) // cat < file2 < file2
		return (cmd__removemiddle(list->next, 2));
	if (list->type == PIPELINE && lastpipe(list) && lastpipe(list)->type >= 60 && lastpipe(list)->type != PIPELINE)
	{
		if (mainredir(v, lastpipe(list)->type, lastpipe(list)->next->line) == 0)
			return (0);
	}
	return (1);
}
