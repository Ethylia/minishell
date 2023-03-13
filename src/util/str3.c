/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:32:40 by francoma          #+#    #+#             */
/*   Updated: 2023/03/13 17:33:48 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	starts_with(const char *s, const char *prefix)
{
	size_t	len;

	len = strln(prefix);
	return (strncmp(s, prefix, len));
}
