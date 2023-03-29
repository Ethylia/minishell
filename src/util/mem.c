/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:19:28 by francoma          #+#    #+#             */
/*   Updated: 2023/03/29 16:11:31 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "util.h"
#include "data.h"

char	*strdupe(const char *s1)
{
	size_t	len;
	char	*s2;
	size_t	i;

	len = strln(s1);
	s2 = malloc(sizeof(*s2) * (len + 1));
	if (!s2)
		exit(EXIT_FAILURE);
	s2[len] = '\0';
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

char	*strndupe(const char *s1, size_t n)
{
	char	*s2;
	size_t	i;

	n = minst(n, strln(s1));
	s2 = malloc(sizeof(*s2) * (n + 1));
	if (!s2)
		exit(EXIT_FAILURE);
	s2[n] = '\0';
	i = 0;
	while (i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

void	*memcopy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

void	*ralloc(void *src, size_t n, size_t sn)
{
	void	*dst;

	dst = malloc(n);
	if (!dst)
		exit(EXIT_FAILURE);
	memcopy(dst, src, sn);
	free(src);
	return (dst);
}
