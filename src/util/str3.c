/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:32:40 by francoma          #+#    #+#             */
/*   Updated: 2023/03/16 16:49:29 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	starts_with(const char *s, const char *prefix)
{
	size_t	len;

	len = strln(prefix);
	return (strncmp(s, prefix, len));
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
