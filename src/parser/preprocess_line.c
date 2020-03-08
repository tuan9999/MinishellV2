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

static t_bool	filter_escape(
		char **input,
		t_vector *new_line)
{
	char	chr;
	size_t	n;

	while (take_char(input, &chr))
	{
		if (chr == '\033')
		{
			if (!(take_char(input, &chr) && chr == '['))
			{
				vector_destroy(new_line);
				return (false);
			}
			(void)take_number(input, &n);
			if (take_char(input, &chr))
				continue ;
		}
		else if (!vector_push(new_line, &chr))
			return (false);
	}
	return (true);
}

t_bool			sanitize_line(
		char **input,
		char **out)
{
	char		chr;
	t_vector	new_line;

	if (!vector_new(&new_line, sizeof(char)))
		return (false);
	filter_escape(input, &new_line);
	chr = '\0';
	if (!vector_push(&new_line, &chr))
		return (false);
	*out = new_line.raw;
	return (true);
}
