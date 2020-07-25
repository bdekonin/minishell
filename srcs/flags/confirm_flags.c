/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   confirm_flags.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 16:57:21 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/25 17:59:07 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int missing_flag(t_vars *v, t_cmd *cmd, char type)
{
	int			ret;
	char		*temp;
	char		*line;
	t_cmd		*newcmd;

	if (type == PIPE)
	{
		ft_printf("pipe> ");
		ret = get_next_line(STDIN_FILENO, &line);
		if (ret < 0)
			return (0);
		newcmd = cmd__ft_lstnew(line[findflag(line, FLAGS)], line);
		if (!newcmd)
		{
			free(line);
			return (-1);
		}
		cmd__ft_lstadd_back(&cmd, newcmd);
		temp = ft_strjoin(v->line, line);
		if (!temp)
		{
			free(line);
			return (0);
		}
		free(v->line);
		v->line = temp;
	}
	else if (type == ANGLEBRACKETLEFT || type == ANGLEBRACKETRIGHT)
	{
		ft_printf("%s: parse error near `\\n'\n", v->__executable->content);
	}
	return (1);
}

int confirm_flags(t_vars *v, char ***argv, t_cmd *cmd, size_t splitsize)
{
	char	*line;
	char	*temp;
	t_cmd	*newcmd;
	int fd;
	v->temp = NULL;

	if (cmd->type && !cmd->next && !missing_flag(v, cmd, cmd->type))
		return (0);
	else
	{
		if (cmd->type && cmd->type == ANGLEBRACKETLEFT)
		{
			// v->fd = open((!ft_strrchr(cmd->next->line, 32) ? cmd->next->line : ft_strrchr(cmd->next->line, 32) + 1), O_RDONLY);
			char *test = ft_substr(cmd->next->line, 0, ft_strchr(cmd->next->line, 32) - cmd->next->line); // leak
			// ft_printf("gnl: [%s] - %d\n", cmd->next->line, ft_strchr(cmd->next->line, 32) - cmd->next->line);
			// ft_printf("test: [%s]\n", test);
			v->fd = open(test, O_RDONLY);
			if (v->fd < 0)
			{
				close(v->fd);
				ft_printf(DIR_NOTFOUND, v->__executable->content, test);
				free(test);
				return (0);
			}
			else
			{
				v->stdin_copy = dup(STDIN_FILENO);
				close(STDIN_FILENO);
				dup2(v->fd, STDIN_FILENO);
			}
			free(test);
		}
		if (cmd->type && (cmd->type == ANGLEBRACKETRIGHT || cmd->type == ANGLEBRACKETDOUBLERIGHT))
		{
			v->stdout_copy = dup(STDOUT_FILENO);
			close(STDOUT_FILENO);
			if (cmd->type == ANGLEBRACKETDOUBLERIGHT)
			{
				v->fd = open(cmd->next->line, O_RDONLY);
				if (v->fd > 0)
					ft_getline(v->fd, &v->temp);
				close(v->fd);
			}
			char *test = ft_substr(cmd->next->line, 0, ft_strchr(cmd->next->line, 32) - cmd->next->line); // leak {cat -e > test doei.txt}
			v->fd = open(test, O_WRONLY | O_CREAT  | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (v->fd < 0)
				return (-1);
			dup2(v->fd, STDOUT_FILENO);
			if (cmd->type == ANGLEBRACKETDOUBLERIGHT)
			{
				if (v->temp)
					write(1, v->temp, ft_strlen(v->temp));
					// return ()
				free(v->temp);
			}
		}
	}
	return (1);
}
