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

#ifndef VECTOR_H
# define VECTOR_H

# include <stddef.h>
# include <ministd.h>

typedef struct	s_vector
{
	size_t		size;
	size_t		capacity;
	size_t		type_size;
	char		*raw;
	void		(*dtor)(struct s_vector *item);
}				t_vector;

t_bool			vector_with_capacity(
				t_vector *self,
				size_t type_size,
				size_t capacity);
t_bool			vector_new(
				t_vector *self,
				size_t type_size);
t_bool			vector_resize(
				t_vector *self,
				size_t capacity);
t_bool			vector_push(
				t_vector *self,
				void *value);
t_bool			vector_getr(
				t_vector *self,
				size_t index,
				void **value);
t_bool			vector_pop(
				t_vector *self,
				void *output);
t_bool			vector_get(
				t_vector *self,
				size_t index,
				void *value);
void			vector_destroy(t_vector *self);
int				vector_foreach(
				t_vector *self,
				int (*f)(void *));
int				vector_foreachc(
				t_vector *self,
				int (*f)(void *, void *),
				void *capture);
t_bool			vector_with_capacity_dtor(
				t_vector *self,
				size_t type_size,
				size_t capacity,
				void (*dtor)(struct s_vector *self));
t_bool			vector_new_dtor(
				t_vector *self,
				size_t type_size,
				void (*dtor)(struct s_vector *self));

#endif
