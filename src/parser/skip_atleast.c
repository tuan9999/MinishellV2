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

#include <parser.h>

t_bool	skip_atleast(
		char **input,
		char matcher,
		size_t times)
{
	size_t occurs;

	occurs = 0;
	while ((*input)[occurs] == matcher)
		occurs += 1;
	*input += occurs;
	return (occurs >= times);
}
