/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   removespace.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:47:30 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/06 16:23:31 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static char		*dquote_incomplete(char *temp)
{
	char *line;
	int ret;

	ret = 1;
	while (ret > 0)
	{
		ft_printf(dquote);
		ret = get_next_line(STDIN_FILENO, &line);
		if (ret < 0)
		{
			free(temp);
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

static char		*quote_complete(t_vars *v, char *temp, char *line)
{
	int j;
	char *dir;

	j = 0;
	while (*line)
	{
		if (*line == '"')
			return (temp);
		if (*line == '$')
		{
			dir = find_environment_variable(v, line + 1);
			if (!dir)
			{
				free(temp);
				return (NULL);
			}
			while (*line && !ft_charsearch(" /|><", *line) && *line != '"')
				line++;
			ft_strcat(temp, dir);
			j = ft_strlen(temp);
			continue;
		}
		temp[j] = *line;
		line++;
		j++;
	}
	return (dquote_incomplete(temp));
}

static char *standard_parse(t_vars *v, char *temp, char *line, int j)
{
	char *dir;

	while (*line)
	{
		if (*line == '$' || *line == '~')
		{
			if (*line == '~')
				dir = v->__homedir;
			else
				dir = find_environment_variable(v, line + 1);
			if (!dir)
			{
				free(temp);
				return (NULL);
			}
			while (*line &&	!ft_charsearch(" /|><", *line))
				line++;
			ft_strcat(temp, dir);
			j = ft_strlen(temp);
			continue;
		}
		if ((*line == 32 && line[1] != '|') || (line[1] == '|' || line[1] == '>'))
			return (temp);
		else if (*line == 92 && line[1] == 32)
			line++;
		temp[j] = *line;
		line++;
		j++;
	}
	return (temp);
}

char *removespace(t_vars *v, char *line)
{
	char *temp;
	int i;

	i = ft_strlen(line) - 1;
	if (i < PATH_MAX)
		temp = ft_calloc(PATH_MAX, sizeof(char));
	else
		temp = ft_calloc(PATH_MAX * 4, sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (line[i] == 32) // change to all whitespaces
		i++;
	if (line[i] == 34) // finish this
		return (quote_complete(v, temp, line + i + 1));
	else
		return (standard_parse(v, temp, line + i, 0));
}


// *line = [84]-[T]
// *line = [101]-[e]
// *line = [115]-[s]
// *line = [116]-[t]
// *line = [92]-[\]
// *line = [32]-[ ]
// *line = [105]-[i]
// *line = [110]-[n]
// *line = [103]-[g]
// *line = [92]-[\]
// *line = [32]-[ ]
// *line = [105]-[i]
// *line = [110]-[n]
// *line = [103]-[g]
// *line = [47]-[/]