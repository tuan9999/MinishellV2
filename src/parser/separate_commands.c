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

static void		switch_mode(
		int *mode,
		char input)
{
	if (*mode == 0)
		*mode = input;
	else if (*mode == input)
		*mode = 0;
}

static t_bool	separate_core_loop(
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

/*
** seperate_commands:
**  string-aware command seperation with ;
**  returns string slices (pointers+length within a string)
**  for each command within that string
**
** tl;dr:
** seperate_commands("echo fuck; echo kitchen");
** returns t_vector<t_string_slice>:
**   { str: 'echo fuck; echo kitchen', length: 9 }
**   { str: ' echo kitchen', length: 13 }
*/

t_bool			separate_commands(
		char *input,
		t_vector *commands)
{
	int				string_mode;
	t_string_slice	str;

	string_mode = 0;
	str.str = input;
	while (*input != '\0')
		if (!separate_core_loop(&input, &string_mode, &str, commands))
			return (false);
	if (string_mode != 0)
		return (false);
	str.len = input - str.str;
	if (!vector_push(commands, &str))
		return (false);
	return (true);
}
