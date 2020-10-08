/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   confirm_flags.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 16:57:21 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/10/08 15:54:09 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int run_angle_right_double(t_vars *v, t_cmd *filename)
{
	char	*file_contents;
	ssize_t	ret;
	int		read_fd;
	
	expansions(v, &filename->token);
	file_contents = NULL;
	ret = read_file(v, filename->token, &file_contents);
	v->stdout_copy = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	v->fd = open(filename->token, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
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

static int run_angle_right_single(t_vars *v, t_cmd *filename)
{
	expansions(v, &filename->token);
	v->stdout_copy = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	v->fd = open(filename->token, O_WRONLY | O_CREAT  | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (v->fd < 0)
		return (0);
	dup2(v->fd, STDOUT_FILENO);
	return (1);
}

static int run_angle_left_single(t_vars *v, t_cmd *filename)
{
	expansions(v, &filename->token);
	v->fd = open(filename->token, O_RDONLY);
	if (v->fd < 0)
	{
		close(v->fd);
		ft_printf(DIR_NOTFOUND, v->default_executable->content, filename->token);
		return (0);
	}
	v->stdin_copy = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	dup2(v->fd, STDIN_FILENO);
	close(v->fd);
	return (1);
}

int	run_flags_command(t_vars *v, t_list *tmp)
{
	int		ret;
	t_cmd	*node;
	t_list	*prev;

	node = tmp->content;
	prev = get_prev_node(v, tmp);
	if (!ft_strncmp((node->token), ">>", 3))
		ret = run_angle_right_double(v, tmp->next->content);
	else if (!ft_strncmp((node->token), ">", 2))
		ret = run_angle_right_single(v, tmp->next->content);
	else if (!ft_strncmp((node->token), "<", 2))
		ret = run_angle_left_single(v, tmp->next->content);
	else
		ret = 1;
	if (!ret)
		return (0);
	if (ft_lstsize(v->cmd) == 2)
	{
		free_cmd_list(v);
		return (ret);
	}
	ft_lst_remove_one(&v->cmd, tmp->next);
	ft_lst_remove_one(&v->cmd, tmp);
	if (!prev && is_redirection(v->cmd))
	{
		reset_std(v);
		return (run_flags_command(v, v->cmd));
	}
	else if (prev && is_redirection(prev->next))
	{
		reset_std(v);
		return (run_flags_command(v, prev->next));
	}
	return (ret);
}
