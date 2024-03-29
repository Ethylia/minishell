/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:21:33 by francoma          #+#    #+#             */
/*   Updated: 2023/03/30 14:44:44 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stddef.h>

typedef unsigned char	t_uchar;

char	*strdupe(const char *s1);
char	*strndupe(const char *s1, size_t n);
void	*memcopy(void *dst, const void *src, size_t n);
char	*strchar(const char *s, int c);

size_t	strln(const char *s);
size_t	strln_del(const char *s, const char del);
int		strcmp(const char *s1, const char *s2);
int		strncmp(const char *s1, const char *s2, size_t n);
int		strcmp_del(const char *s1, const char *s2, const char del);
char	*concatstr(size_t n, ...);
char	*concatstr_ln(size_t n, ...);
int		is_ws(char c);
void	skipwhite(const char **line);
size_t	countwhite(const char *line);
void	*ralloc(void *src, size_t n, size_t sn);
int		isalphaunder(char c);
int		stralphanumunder(const char *c);
char	*intoa(int n);
t_uchar	atouc(const char *s);

int		starts_with(const char *s, const char *prefix);

size_t	minst(size_t a, size_t b);

#endif
