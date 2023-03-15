/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:34:57 by francoma          #+#    #+#             */
/*   Updated: 2023/03/15 13:19:58 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "util.h"

static char	*alloc_res(size_t n, va_list ori_va)
{
	size_t	ln;
	size_t	i;
	va_list	va;

	va_copy(va, ori_va);
	ln = 0;
	i = 0;
	while (i < n)
	{
		ln += strln(va_arg(va, char *));
		i++;
	}
	va_end(va);
	return (malloc(sizeof(char) * (ln + 1)));
}

static char	*copy_strs(char *dst, size_t n, va_list va)
{
	size_t	i;
	size_t	ln;
	size_t	whole_ln;
	char	*str;

	whole_ln = 0;
	i = 0;
	while (i < n)
	{
		str = va_arg(va, char *);
		ln = strln(str);
		memcopy(dst + whole_ln, str, ln);
		whole_ln += ln;
		i++;
	}
	dst[whole_ln] = '\0';
	return (dst);
}

char	*concatstr(size_t n, ...)
{
	va_list	va;
	char	*res;

	va_start(va, n);
	res = alloc_res(n, va);
	if (!res)
		return (NULL);
	copy_strs(res, n, va);
	va_end(va);
	return (res);
}

int	whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}
