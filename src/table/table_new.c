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

#include <table.h>
#include <stdlib.h>

static void	cleanup_table(t_table *self)
{
	t_table_entry	entry;

	while (vector_pop(self, &entry))
	{
		free(entry.key);
		free(entry.value);
	}
}

t_bool		table_new(t_table *self)
{
	return (vector_new_dtor(self, sizeof(t_table_entry), cleanup_table));
}
