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

#ifndef TABLE_H
# define TABLE_H

# include <vector.h>

typedef struct	s_table_entry
{
	char		*key;
	char		*value;
}				t_table_entry;

# define ULL_MAX -1UL

typedef t_vector	t_table;

t_bool			table_new(t_table *self);
char			*table_get(t_table *self, char *key);
t_table_entry	*table_get_entry(t_table *self, char *key);
t_bool			table_insert(t_table *self, char *key, char *value);
void			table_destroy(t_table *self);
t_bool			table_remove(t_table *self, char *key);

#endif
