/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 07:29:06 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/31 16:08:08 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vector.h"
#include "util.h"

void	v_pushelem(t_vector *v, void *data)
{
	if (v->size == v->capacity)
	{
		v->data = ralloc(v->data, v->capacity * v->elem_size * 2,
				v->size * v->elem_size);
		v->capacity *= 2;
	}
	memcopy(v->data + v->size * v->elem_size, &data, v->elem_size);
	++(v->size);
}
