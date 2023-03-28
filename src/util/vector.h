/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:34:29 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/28 16:37:12 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdint.h>
# include <stddef.h>

typedef struct s_vector {
	int8_t	*data;
	size_t	size;
	size_t	capacity;
	size_t	elem_size;
}	t_vector;

void	v_init(t_vector *v, size_t elem_size, size_t capacity);
void	v_free(t_vector *v);
void	v_free_elems(t_vector *v);
void	v_push(t_vector *v, const void *elem);
size_t	v_pushstr(t_vector *arg, const char *str);
void	v_resize(t_vector *v, size_t size);

#endif
