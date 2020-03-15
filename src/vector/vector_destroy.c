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

void	vector_destroy(t_vector *self)
{
	if (self->dtor)
		self->dtor(self);
	free(self->raw);
	self->raw = NULL;
	self->capacity = 0;
	self->size = 0;
	self->type_size = 0;
	self->dtor = NULL;
}
