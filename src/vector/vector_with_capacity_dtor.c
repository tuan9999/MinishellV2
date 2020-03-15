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
#include <stdlib.h>

t_bool	vector_with_capacity_dtor(
		t_vector *self,
		size_t type_size,
		size_t capacity,
		void (*dtor)(struct s_vector *self))
{
	if (!vector_with_capacity(self, type_size, capacity))
		return (false);
	self->dtor = dtor;
	return (true);
}
