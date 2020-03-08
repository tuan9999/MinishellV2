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

#include <stdlib.h>
#include <stdio.h>
#include <runtime_loop.h>
#include <ministd.h>

static int	read_until_end(
		char **builder,
		char *chr,
		int *length,
		int *capacity)
{
	if (!read_char(chr))
	{
		free(*builder);
		return (-1);
	}
	while (*chr != '\n' && *chr != EOF)
	{
		if (*length == *capacity)
		{
			*builder = ft_realloc(*builder, *capacity, *capacity * 2);
			*capacity *= 2;
			if (*builder == NULL)
				return (-1);
		}
		(*builder)[*length] = *chr;
		*length += 1;
		if (!read_char(chr))
		{
			free(*builder);
			return (-1);
		}
	}
	return (*chr != -1);
}

int			read_line(
		char **line,
		int eof_matters)
{
	int		length;
	int		capacity;
	char	*builder;
	char	chr;
	int		res;

	length = 0;
	capacity = 256;
	builder = malloc(capacity * sizeof(char));
	if (builder == NULL)
		return (-1);
	res = read_until_end(&builder, &chr, &length, &capacity);
	while (eof_matters && res == 0 && length != 0)
		res = read_until_end(&builder, &chr, &length, &capacity);
	if (res == -1)
		return (-1);
	builder = ft_realloc(builder, length, length + 1);
	if (builder == NULL)
		return (-1);
	builder[length] = '\0';
	*line = builder;
	return (res);
}
