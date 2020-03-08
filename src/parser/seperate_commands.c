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
#include <vector.h>

static t_bool	is_string_quote(char c)
{
	return (c == STRING_SINGLE_QUOTE || c == STRING_DOUBLE_QUOTE);
}

static void		switch_mode(
		int *mode,
		char input)
{
	if (*mode == 0)
		*mode = input;
	else if (*mode == input)
		*mode = 0;
}

static t_bool	seperator_core_loop(
		char **input,
		int *string_mode,
		t_string_slice *str,
		t_vector *commands)
{
	if (**input == CMD_SEPERATOR && *string_mode == 0)
	{
		str->len = *input - str->str;
		if (!vector_push(commands, str))
			return (false);
		str->str = *input + 1;
	}
	else if (is_string_quote(**input))
		switch_mode(string_mode, **input);
	else if (**input == '\\' && *string_mode != '\'')
	{
		*input += 1;
		if (**input == '\0')
			return (false);
	}
	*input += 1;
	return (true);
}

t_bool			seperate_commands(
		char *input,
		t_vector *commands)
{
	int				string_mode;
	t_string_slice	str;

	string_mode = 0;
	str.str = input;
	while (*input != '\0')
		if (!seperator_core_loop(&input, &string_mode, &str, commands))
			return (false);
	if (string_mode != 0)
		return (false);
	str.len = input - str.str;
	if (!vector_push(commands, &str))
		return (false);
	return (true);
}
