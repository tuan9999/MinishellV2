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

t_bool			table_remove(
		t_table *self,
		char *key)
{
	t_table_entry	*maybe;

	maybe = table_get_entry(self, key);
	if (maybe != NULL)
	{
		free(maybe->key);
		free(maybe->value);
		maybe->key = key;
		maybe->value = NULL;
		return (true);
	}
	else
		return (false);
}
