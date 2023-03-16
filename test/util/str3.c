/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:32:40 by francoma          #+#    #+#             */
/*   Updated: 2023/03/16 15:31:06 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	starts_with(const char *s, const char *prefix)
{
	size_t	len;

	len = strln(prefix);
	return (strncmp(s, prefix, len));
}

size_t	nextarg(const char *s)
{
	size_t	i;
	int		quote;

	i = -1;
	quote = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (!quote)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
		}
		else if (whitespace(s[i]) && !quote)
			break ;
	}
	return (i);
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
