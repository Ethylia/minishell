#ifndef VECTOR_H
# define VECTOR_H

# include <stddef.h>

typedef struct s_vector {
	void	*data;
	size_t	size;
	size_t	capacity;
	size_t	elem_size;
} t_vector;

void	v_init(t_vector *v, size_t elem_size, size_t capacity);
void	v_free(t_vector *v);
void	v_push(t_vector *v, void *elem);
void	v_resize(t_vector *v, size_t size);

#endif