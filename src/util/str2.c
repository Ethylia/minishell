/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:32:40 by francoma          #+#    #+#             */
/*   Updated: 2023/03/17 15:18:41 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	starts_with(const char *s, const char *prefix)
{
	size_t	len;

	len = strln(prefix);
	return (strncmp(s, prefix, len));
}

char	*strchar(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char) c)
		return ((char *)&s[i]);
	return (NULL);
}

int	whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	skipwhite(const char **line)
{
	while (whitespace(**line))
		++(*line);
}

size_t	countwhite(const char *line)
{
	size_t	i;

	i = 0;
	while (whitespace(line[i]))
		++i;
	return (i);
}
