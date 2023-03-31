/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:39:40 by francoma          #+#    #+#             */
/*   Updated: 2023/03/31 10:06:45 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/util.h"

static size_t	count_asterisks(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count] && str[count] == '*')
		count++;
	return (count);
}

static int	matches_literal_part(const char *literal, size_t literal_len,
	const char *candidate)
{
	return (strncmp(literal, candidate, literal_len) == 0
		&& (literal[literal_len] == '*'
			|| (!literal[literal_len] && !candidate[literal_len])));
}

static size_t	substitution_len(const char *literal, size_t literal_len,
	const char *candidate)
{
	size_t	i;

	i = 0;
	while (candidate[i])
	{
		if (strncmp(&candidate[i], literal, literal_len) == 0
			&& (literal[literal_len] == '*'
				|| (!literal[literal_len] && !candidate[i + literal_len])))
			return (i);
		i++;
	}
	return (0);
}

int	matches_wildcard(const char *wildcard, const char *candidate)
{
	size_t	i;
	size_t	j;
	size_t	literal_len;

	i = 0;
	j = 0;
	if (starts_with(wildcard, "*") && starts_with(candidate, "."))
		return (0);
	if (starts_with(wildcard, "./"))
		wildcard += 2;
	while (1)
	{
		literal_len = strln_del(wildcard + i, '*');
		if (!matches_literal_part(wildcard + i, literal_len, candidate + j))
			return (0);
		i += literal_len;
		j += literal_len;
		i += count_asterisks(wildcard + i);
		literal_len = strln_del(wildcard + i, '*');
		j += substitution_len(wildcard + i, literal_len, candidate + j);
		if (!wildcard[i])
			return (!candidate[j] || !i || wildcard[i - 1] == '*');
	}
	return (1);
}
