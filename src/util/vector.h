/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:34:29 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/31 16:11:50 by francoma         ###   ########.fr       */
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
size_t	v_pushstrn(t_vector *arg, const char *str, size_t n);
void	v_free_elems(t_vector *v);
void	v_push(t_vector *v, const void *elem);
size_t	v_pushstr(t_vector *arg, const char *str);
void	v_pushelem(t_vector *v, void *data);

#endif
