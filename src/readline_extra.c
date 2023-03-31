/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:23:54 by francoma          #+#    #+#             */
/*   Updated: 2023/03/31 17:00:40 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/util.h"
#include "builtins/builtins.h"
#include "def.h"
#include "util/vector.h"
#include "readline_extra.h"

static void	insertfirst(t_vector *vec, char *s)
{
	char	*tmp;

	tmp = ((char **)vec->data)[0];
	((char **)vec->data)[0] = s;
	v_push(vec, &tmp);
}

static char	*longuestcommon(t_vector *vec)
{
	t_vector	str;
	size_t		i;
	size_t		j;

	v_init(&str, sizeof(char), 8);
	i = 0;
	while (1)
	{
		j = -1;
		while (++j < vec->size - 1)
		{
			if (((char **)vec->data)[j + 1][i] != ((char **)vec->data)[j][i]
				|| !((char **)vec->data)[j + 1][i])
			{
				v_push(&str, "\0");
				return ((char *)str.data);
			}
		}
		v_push(&str, &((char **)vec->data)[j][i]);
		++i;
	}
	v_push(&str, "\0");
	return ((char *)str.data);
}

char	**completion(const char *s, int start, int end)
{
	t_vector	res;
	size_t		i;

	if (end - start <= 0 || !s || start)
		return (NULL);
	i = -1;
	v_init(&res, sizeof(char *), 8);
	while (get_builtins_names()[++i])
		if (!strncmp(get_builtins_names()[i], s, end - start))
			v_pushelem(&res, strdupe(get_builtins_names()[i]));
	get_path_executables(s, end - start, &res);
	if (res.size)
	{
		if (res.size > 1)
			insertfirst(&res, longuestcommon(&res));
		v_push(&res, NULLPTR);
		return ((char **)res.data);
	}
	free(res.data);
	return (NULL);
}
