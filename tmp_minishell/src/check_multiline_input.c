/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_multiline_input.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 20:09:11 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/09/23 15:33:17 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_str_expand(char **str, size_t size)
{
	size_t	stringlength;
	char	*temp;

	if (size == 0)
		return (0);
	if (size < 0)
		return (-1);
	stringlength = ft_strlen(*str);
	temp = ft_calloc(stringlength + size, sizeof(char));
	if (!temp)
		return (-1);
	temp = ft_memcpy(temp, *str, stringlength);
	free(*str);
	*str = temp;
	return (1);
}

static char *ft_quote(char *oldstring, const char *type)
{
	size_t	length;
	char	*temp;
	char	*line;
	char	*newstring;

	temp = ft_calloc(1, sizeof(char));
	if (!temp)
		return (NULL);
	while (1)
	{
		ft_printf(DQUOTE);
		get_next_line(STDIN_FILENO, &line); //check return!?
		length = ft_strlen(line) + 1; // 1 for newline
		if (ft_str_expand(&temp, length + 1) < 0) // 1 for \0		//malloc
		{
			free(temp);
			free(line);
			return (NULL);
		}
		ft_strlcat(temp, "\n", ft_strlen(temp) + 2);
		ft_strlcat(temp, line, length + ft_strlen(temp));
		free(line);
		if (ft_counter(temp, type))
			break ;
	}
	newstring = ft_strjoin(oldstring, temp); 						//malloc
	free(temp);
	free(oldstring);
	return (newstring);
}

void    check_multiline_input(t_vars *v, char **arg)
{
    if (ft_counter(*arg, "\"") % 2 || ft_counter(*arg, "\'") % 2)
    {
        *arg = ft_quote(*arg, (ft_counter(*arg, "\"") % 2) ? "\"" : "\'");
		if (!*arg)
			ft_exit_error(v, 1);
    }
}
