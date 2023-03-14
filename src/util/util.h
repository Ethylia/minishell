/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:21:33 by francoma          #+#    #+#             */
/*   Updated: 2023/03/14 14:03:34 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stddef.h>

char	*strdup(const char *s1);
void	*memcpy(void *dst, const void *src, size_t n);

size_t	strln(const char *s);
size_t	strln_del(const char *s, const char del);
int		strcmp(const char *s1, const char *s2);
int		strncmp(const char *s1, const char *s2, size_t n);
int		strcmp_del(const char *s1, const char *s2, const char del);
char	*concatstr(size_t n, ...);
int		whitespace(char c);
size_t	nextarg(const char *s);

int		starts_with(const char *s, const char *prefix);

#endif
