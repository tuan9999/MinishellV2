/* ************************************************************************** */
/*                                                                            */
/*   Project: memeshell420                                ::::::::            */
/*   Members: dpattij, tuperera                         :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

t_bool	vector_resize(
		t_vector *self,
		size_t capacity)
{
	if (capacity <= self->capacity)
		return (false);
	self->raw = ft_realloc(self->raw, self->size * self->type_size,
			capacity * self->type_size);
	if (self->raw == NULL)
		return (false);
	self->capacity = capacity;
	return (true);
}
