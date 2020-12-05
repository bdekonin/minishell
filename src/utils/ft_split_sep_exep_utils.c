/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_sep_exep_utils.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 14:28:55 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/05 09:22:27 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	skip_quotations_i(const char *cli, size_t i, char quotation)
{
	i++;
	while (cli[i] && cli[i] != quotation)
	{
		if (cli[i] == '\\' && cli[i + 1] == '\\')
			i++;
		else if (cli[i] == '\\' && cli[i + 1] == '\"')
			i++;
		i++;
	}
	return (i);
}

size_t			get_start_split(const char *src, char *sep, size_t i)
{
	while (src[i] != '\0' && ft_charsearch(src[i], sep))
		i++;
	return (i);
}

size_t			get_len_split(const char *src, char *sep, size_t start)
{
	size_t	i;
	size_t	len;

	i = start;
	len = start;
	while (src[i] != '\0' && !ft_charsearch(src[i], sep))
	{
		if (src[i] == '\\')
			i++;
		else if (src[i] == '\'')
			i = skip_quotations_i(src, i, '\'');
		else if (src[i] == '\"')
			i = skip_quotations_i(src, i, '\"');
		i++;
	}
	return (i - len);
}
