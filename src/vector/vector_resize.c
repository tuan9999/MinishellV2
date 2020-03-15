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
	char	*new;

	if (capacity <= self->capacity)
		return (false);
	new = ft_realloc(self->raw, self->size * self->type_size,
			capacity * self->type_size);
	if (new == NULL)
	{
		vector_destroy(self);
		return (false);
	}
	self->raw = new;
	self->capacity = capacity;
	return (true);
}
