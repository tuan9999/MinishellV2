/* ************************************************************************** */
/*                                                                            */
/*   File: ministd.h                                      ::::::::            */
/*   Created on 2020/03/04 00:40:54                     :+:    :+:            */
/*   Created by dpattij <dpattij@student.codam.nl>     +:+                    */
/*                                                    +#+                     */
/*   void *data = NULL;                              +#+                      */
/*   while (data == NULL)                           #+#    #+#                */
/*       data = malloc(1337 * 42 * 21);            ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISTD_H
# define MINISTD_H

typedef enum	e_bool
{
	false = 0,
	true = 1
}				t_bool;

char	*ft_realloc(
		char *ptr,
		size_t ocapacity,
		size_t capacity);

#endif
