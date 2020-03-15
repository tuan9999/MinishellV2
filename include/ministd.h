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
void	ft_perror(char *str);

#endif
