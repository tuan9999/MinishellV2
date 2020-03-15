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

t_bool	vector_new_dtor(
		t_vector *self,
		size_t type_size,
		void (*dtor)(struct s_vector *self))
{
	return (vector_with_capacity_dtor(self, type_size, 0, dtor));
}
