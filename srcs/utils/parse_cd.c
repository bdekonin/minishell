/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:47:30 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/22 11:38:48 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int	copy_dollar_mark(t_vars *v, char *dst, char *src, size_t *i, size_t *j)
{
	size_t env_len;
	char *env_name;
	char *env_content;

	*i += 1;
	env_len = 0;
	//while (ft_charsearch_bool("\"\'' '\\$/", src[*i + env_len])
	while (src[*i + env_len] != '\0' && src[*i + env_len] != '\"' && src[*i + env_len] != ' ' && src[*i + env_len] != '\\' && src[*i + env_len] != '$' && src[*i + env_len] != '/')
		env_len++;
	if (env_len == 0)
		return (0); //env var name has len of 0. Don't delete this check.
	env_name = src + *i;
	env_content = find_environment_variable(v, env_name, &env_len);
	if (!env_content)
		return (0); //env name not in env list
	ft_strlcat(dst + *j, env_content, PATH_MAX);
	*i += env_len - 1;
	*j += ft_strlen(env_content);
	return (1);
}

static int	copy_comment_mark(char *src, size_t *i)
{
	*i += 1;
	while (src[*i] != '\0')
		*i += 1;
	return (1);
}

static int	copy_double_quote(t_vars *v, char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
	while (src[*i] != '\0' && src[*i] != '\"')
	{
		if (src[*i] == '$')
		{
			copy_dollar_mark(v, dst, src, i, j); //check return
			*i += 1;
		}
		else
		{
			dst[*j] = src[*i];
			*i += 1;
			*j += 1;
		}
	}
	return (1);
}

static int	copy_single_quote(char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
	while (src[*i] != '\0' && src[*i] != '\'')
	{
		dst[*j] = src[*i];
		*i += 1;
		*j += 1;
	}
	return (1);
}

static int copy_backslash(char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
	dst[*j] = src[*i];
	*j += 1;
	return (1);
}

static int get_directory_len(t_vars *v, char *dst, char *src)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (src[i] != '\0') // && dst[j] != '\0';
	{
		if (src[i] == '\\')
			copy_backslash(dst, src, &i, &j);
		else if (src[i] == '\'')
			copy_single_quote(dst, src, &i, &j);
		else if (src[i] == '\"')
			copy_double_quote(v, dst, src, &i, &j);
		else if (src[i] == '$')
			copy_dollar_mark(v, dst, src, &i, &j);
		else if (src[i] == '#' && i == 0)
			copy_comment_mark(src, &i);
		else
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	return (1);
}

char	*parse_cd(t_vars *v, char *line)
{
	char *src;
	char *dst;
	size_t i;
	ssize_t ret;

	i = 0;
	src = line + 1;
	dst = ft_calloc(PATH_MAX, sizeof(char)); //PATH_MAX + 1?
	if (!dst)
		return (NULL);
	ret = get_directory_len(v, dst, src);
	if (ret < 0)
		return (0); //error
	return (dst);
}



// static char		*dquote_incomplete(char *temp, int c)
// {
// 	char *line;
// 	int ret;

// 	ret = 1;
// 	while (ret > 0)
// 	{
// 		ft_printf(dquote);
// 		ret = get_next_line(STDIN_FILENO, &line);
// 		if (ret < 0)
// 		{
// 			free(temp);
// 			return (NULL);
// 		}
// 		ft_strcat(temp, line);
// 		if (ft_counter(line, c) == 1)
// 		{
// 			free(line);
// 			temp[ft_strlen(temp) - 1] = '\0';
// 			return (temp);
// 		}
// 		free(line);
// 	}
// 	return (temp);
// }

// static char		*quote_complete(t_vars *v, char *temp, char *line, int c)
// {
// 	int j;
// 	char *dir;

// 	j = 0;
// 	while (*line)
// 	{
// 		if (*line == c)
// 			return (temp);
// 		if (*line == '$')
// 		{
// 			dir = find_environment_variable(v, line + 1);
// 			if (!dir)
// 			{
// 				free(temp);
// 				return (NULL);
// 			}
// 			while (*line && !ft_charsearch(" /|><", *line) && *line != c)
// 				line++;
// 			ft_strcat(temp, dir);
// 			j = ft_strlen(temp);
// 			continue;
// 		}
// 		temp[j] = *line;
// 		line++;
// 		j++;
// 	}
// 	return (dquote_incomplete(temp, c));
// }

// static char *standard_parse(t_vars *v, char *temp, char *line, int j)
// {
// 	char *dir;

// 	while (*line)
// 	{
// 		if (*line == '$' || *line == '~')
// 		{
// 			if (*line == '~')
// 				dir = v->__homedir->content;
// 			else
// 				dir = find_environment_variable(v, line + 1);
// 			if (!dir)
// 			{
// 				free(temp);
// 				return (NULL);
// 			}
// 			while (*line &&	!ft_charsearch(" /|><", *line))
// 				line++;
// 			ft_strcat(temp, dir);
// 			j = ft_strlen(temp);
// 			continue;
// 		}
// 		if ((*line == 32 && line[1] != '|') || (line[1] == '|' || line[1] == '>'))
// 			return (temp);
// 		else if (*line == 92 && line[1] == 32)
// 			line++;
// 		temp[j] = *line;
// 		line++;
// 		j++;
// 	}
// 	return (temp);
// }

	
	// i = ft_strlen(line) - 1;
	// if (i < PATH_MAX)
	// 	temp = ft_calloc(PATH_MAX, sizeof(char));
	// else
	// 	temp = ft_calloc(PATH_MAX * 4, sizeof(char));
	// if (!temp)
	// 	return (NULL);
	// i = 0;
	// while (line[i] == 32 || line[i] == '\t')
	// 	i++;
	// if (line[i] == 34 || line[i] == 39)
	// 	return (quote_complete(v, temp, line + i + 1, line[i]));
	// else
	// 	return (standard_parse(v, temp, line + i, 0));
