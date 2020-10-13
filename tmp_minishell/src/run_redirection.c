/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_redirection.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 11:44:41 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/13 13:23:47 by lverdoes      ########   odam.nl         */
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

static int run_angle_right_double(t_vars *v, char *filename)
{
	char	*file_contents;
	ssize_t	ret;
	int		read_fd;
	
	expansion(v, &filename);
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
	expansion(v, &filename);
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
	expansion(v, &filename);
	v->fd = open(filename, O_RDONLY);
	if (v->fd < 0)
	{
		close(v->fd);
		ft_printf(DIR_NOTFOUND, v->default_executable->content, filename);
		return (0);
	}
	v->stdin_copy = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	dup2(v->fd, STDIN_FILENO);
	close(v->fd);
	return (1);
}

int	run_redirection(t_vars *v, t_list *first_cmd, t_list *flag)
{
	int ret;

//	printf("firstcmd = [%s]\t\t[%p]\t[%p]\n", first_cmd->content, first_cmd->content, first_cmd);
//	printf("tmp cont = [%s]\t\t[%p]\t[%p]\n", flag->content, flag->content, flag);
//	printf("file con = [%s]\t\t[%p]\t[%p]\n", flag->next->content, flag->next->content, flag->next);
	if (!ft_strncmp((flag->content), ">>", 3))
		ret = run_angle_right_double(v, flag->next->content);
	else if (!ft_strncmp((flag->content), ">", 2))
		ret = run_angle_right_single(v, flag->next->content);
	else if (!ft_strncmp((flag->content), "<", 2))
		ret = run_angle_left_single(v, flag->next->content);
	else
		ret = 0;
	if (!ret)
		return (0);
	return (ret);
}
