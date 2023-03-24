/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:11 by francoma          #+#    #+#             */
/*   Updated: 2023/03/24 08:55:13 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	strln(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	strln_del(const char *s, const char del)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != del)
		len++;
	return (len);
}

int	strcmp(const char *s1, const char *s2)
{
	int		diff;
	size_t	i;

	diff = 0;
	i = 0;
	while (diff == 0 && (s1[i] || s2[i]))
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	return (diff);
}

int	strcmp_del(const char *s1, const char *s2, const char del)
{
	int		diff;
	size_t	i;

	diff = 0;
	i = 0;
	while (!diff)
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		if ((s1[i] == '\0' && s2[i] == del)
			|| (s1[i] == del && s2[i] == '\0'))
			return (0);
		i++;
	}
	return (diff);
}

int	strncmp(const char *s1, const char *s2, size_t n)
{
	int		diff;
	size_t	i;

	diff = 0;
	i = 0;
	while (diff == 0 && (s1[i] || s2[i]) && i < n)
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	return (diff);
}
