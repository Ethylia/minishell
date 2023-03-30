/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:39:27 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/30 08:59:40 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

int	isalphaunder(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	stralphanumunder(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] && c[i] != '=')
	{
		if (!isalphaunder(c[i]) && (c[i] < '0' || c[i] > '9'))
			return (0);
		++i;
	}
	return (1);
}

size_t	numlen(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 9)
	{
		len++;
		n /= 10;
	}
	len++;
	return (len);
}

char	*intoa(int n)
{
	char	*str;
	size_t	len;

	len = numlen(n);
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
		exit(EXIT_FAILURE);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 9)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	str[--len] = n + '0';
	return (str);
}

unsigned char	atouc(const char *str)
{
	ssize_t	res;
	int		sign;

	if (!str)
		return (0);
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	res = 0;
	while (*str)
	{
		res *= 10;
		res += *str - '0';
		str++;
	}
	return (sign * res);
}
