/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 07:29:06 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/27 07:30:45 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "util.h"

void	v_push(t_vector *v, void *data)
{
	if (v->size == v->capacity)
	{
		v->data = ralloc(v->data, v->capacity * v->elem_size * 2,
				v->size * v->elem_size);
		v->capacity *= 2;
	}
	memcopy((char *)v->data + v->size * v->elem_size, data, v->elem_size);
	++(v->size);
}

void	v_resize(t_vector *v, size_t size)
{
	if (size > v->capacity)
	{
		v->data = ralloc(v->data, size * v->elem_size,
				v->size * v->elem_size);
		v->capacity = size;
	}
}

void	v_init(t_vector *v, size_t elem_size, size_t capacity)
{
	v->data = malloc(elem_size * capacity);
	if (!v->data)
	{
		freedata();
		exit(1);
	}
	v->size = 0;
	v->capacity = capacity;
	v->elem_size = elem_size;
}

void	v_free(t_vector *v)
{
	free(v->data);
}
