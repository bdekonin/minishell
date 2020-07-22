/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_quote.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 20:09:11 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/22 11:22:01 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

char *ft_quote(char *oldstring, char type)
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
		get_next_line(STDIN_FILENO, &line);
		length = ft_strlen(line) + 1; // 1 for newline
		if (ft_strexpand(&temp, length + 1) < 0) // 1 for \0
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
	newstring = ft_strjoin(oldstring, temp);
	free(temp);
	free(oldstring);
	return (newstring);
}