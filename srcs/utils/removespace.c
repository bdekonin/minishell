/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   removespace.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:47:30 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/03 23:00:23 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/*
** Returns the read environment variable
**
** @param  t_vars *v	vars struct
** @param  char *line	Current command line
**
** @return char*		Returns pointer of the valid variable
*/

static char *find_environment_variable(t_vars *v, char *line)
{
	t_env		*lst;
	int			j;
	char		*name;

	if (*line == '?')
		return (v->history_head->output);
	name = ft_strdup(line);
	if (!name)
		return (NULL);
	j = 0;
	lst = v->env_head;
	while (name[j] && name[j] != ' ' && name[j] != '/' && name[j] != '|' \
	&& name[j] != '>')
		j++;
	name[j] = '\0';
	while (lst)
	{
		if (!ft_strncmp(lst->name, name, ft_strlen(name)))
		{
			free(name);
			return (lst->content);
		}
		lst = lst->next;
	}
	free(name);
	return (v->__homedir);
}

static char *dquote_incomplete(char *temp)
{
	char *line;
	int ret;

	ret = 1;
	temp[ft_strlen(temp) - 1] = '\0';
	while (ret > 0)
	{
		ft_printf("dquote> ");
		ret = get_next_line(STDIN_FILENO, &line);
		if (ret < 0)
		{
			free(temp);
			//erno 12
			return (NULL);
		}
		ft_strcat(temp, line);
		if (ft_counter(line, '"') == 1)
		{
			free(line);
			temp[ft_strlen(temp) - 1] = '\0';
			return (temp);
		}
		free(line);
	}
	return (temp);
}

static char *quote_complete(t_vars *v, int i, char *temp, char *line)
{
	int j;
	char *dir;

	j = 0;
	while (line[i])
	{
		if (line[i] == '"')
			return (temp);
		if (line[i] == '$')
		{
			dir = find_environment_variable(v, line + i + 1);
			if (!dir)
			{
				free(temp);
				return (NULL);
			}
			while (line[i] && line[i] != ' ' &&
				line[i] != '/' &&
				line[i] != '|' && line[i] != '>' && line[i] != '"')
				i++;
			ft_strcat(temp, dir);
			j = ft_strlen(temp);
			continue;
		}
		temp[j] = line[i];
		i++;
		j++;
	}
	return (dquote_incomplete(temp));
}

char *removespace(t_vars *v, char *line)
{
	char *dir;
	char *temp;
	int i;
	int j;

	i = ft_strlen(line) - 1;
	j = 0;
	if (i < PATH_MAX)
		temp = ft_calloc(PATH_MAX, sizeof(char));
	else
		temp = ft_calloc(PATH_MAX * 4, sizeof(char));
	if (!temp)
	{
		// errno = 12;
		return (NULL);
	}
	i = 0;
	dir = NULL;
	while (line[i] == 32) // change to all whitespaces
		i++;
	if (line[i] == 34) // finish this
		temp = quote_complete(v, i + 1, temp, line);
	else if (!dir) // Standerd parsing
	{
		while (line[i])
		{
			if (line[i] == '$' || line[i] == '~')
			{
				if (line[i] == '~')
					dir = v->__homedir;
				else
					dir = find_environment_variable(v, line + i + 1);
				if (!dir)
				{
					free(temp);
					return (NULL);
				}
				while (line[i] && line[i] != ' ' &&
					line[i] != '/' &&
					line[i] != '|' && line[i] != '>')
					i++;
				ft_strcat(temp, dir);
				j = ft_strlen(temp);
				continue;
			}
			if (line[i + 1] == '|' || line[i + 1] == '>')
				return (temp);
			if (line[i] == 32 && line[i + 1] != '|')
				return (temp);
			else if (line[i] == 92 && line[i + 1] == 32)
				i++;
			temp[j] = line[i];
			i++;
			j++;
		}
		return (temp);
	}
	return (temp);
}