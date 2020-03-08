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

t_bool	vector_pop(
		t_vector *self,
		void *output)
{
	t_bool	result;

	if (self->size == 0)
		return (false);
	result = vector_get(self, self->size - 1, output);
	if (result)
		self->size -= 1;
	return (result);
}
