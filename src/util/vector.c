/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 07:29:06 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/29 16:11:52 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "data.h"
#include "vector.h"
#include "util.h"

void	v_push(t_vector *v, const void *data)
{
	if (v->size == v->capacity)
	{
		v->data = ralloc(v->data, v->capacity * v->elem_size * 2,
				v->size * v->elem_size);
		v->capacity *= 2;
	}
	memcopy(v->data + v->size * v->elem_size, data, v->elem_size);
	++(v->size);
}

size_t	v_pushstr(t_vector *arg, const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		v_push(arg, str + i++);
	return (i);
}

size_t	v_pushstrn(t_vector *arg, const char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (str[i] && i < n)
		v_push(arg, str + i++);
	return (i);
}

void	v_init(t_vector *v, size_t elem_size, size_t capacity)
{
	v->data = malloc(elem_size * capacity);
	if (!v->data)
		exit(EXIT_FAILURE);
	v->size = 0;
	v->capacity = capacity;
	v->elem_size = elem_size;
}

void	v_free_elems(t_vector *v)
{
	size_t	i;

	if (!v->data)
		return ;
	i = 0;
	while (i < v->size)
		free(*((void **)(v->data) + i++));
	free(v->data);
	v->data = 0;
	v->size = 0;
	v->capacity = 0;
}
