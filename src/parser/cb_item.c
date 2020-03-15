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

t_bool	cb_string_core(
		char **input,
		size_t *len,
		t_vector *out)
{
	char chr;

	chr = (*input)[*len];
	if (chr == '\\' && **input != '\'')
	{
		if (is_escapable((*input)[*len + 1]))
		{
			*len += 1;
			chr = (*input)[*len];
		}
		else if ((*input)[*len + 1] != '\0')
		{
			if (!vector_push(out, &chr))
				return (false);
			*len += 1;
			chr = (*input)[*len];
		}
		else
		{
			vector_destroy(out);
			return (false);
		}
	}
	return (!(chr != '\0' && !vector_push(out, &chr)));
}

/*
** cb_string:
**  parse a string with ' or " quotes
**  return the insides of that string through output
**  most of the core loop is inside of cb_string_core
**
**  handles escape characters in DOUBLE QUOTE STRINGS ("bruh")
**   and handles them literally in SINGLE QUOTE STRINGS ('bruh').
**
**  escape characters are only escaped if the next character is escapable,
**  otherwise the escape indicator (backslash, '\') is handled literally.
**
**  tl;dr:
**
**  cb_string("\"hello, world!\"") -> hello, world!
**  cb_string("'hello, world!'") -> hello, world!
**  cb_string("\"hello\world\"") -> hello\world
**  cb_string("\"hello\"world\"") -> hello"world
**  cb_string("'hello\'world'") -> hello\'world
**  cb_string("'hello\\world'") -> hello\\world
**  cb_string("\"hello\\world\"") -> hello\world
*/

t_bool	cb_string(
		char **input,
		size_t *len,
		t_vector *out)
{
	char	start;

	start = (*input)[*len];
	if (start != '\'' && start != '\"')
	{
		vector_destroy(out);
		return (false);
	}
	*len += 1;
	while ((*input)[*len] != start)
	{
		if (!cb_string_core(input, len, out))
			return (false);
		*len += 1;
	}
	*len += 1;
	return (true);
}

t_bool	cb_unit_core(
		char **input,
		size_t *len,
		t_vector *out)
{
	char	chr;

	while (is_not_control((*input)[*len]) && (*input)[*len] != '\0')
	{
		chr = (*input)[*len];
		if (chr == '\\' && (*input)[*len + 1] != '\0')
			*len += 1;
		else if (chr == '\\')
		{
			vector_destroy(out);
			return (false);
		}
		else if ((chr == '\"' || chr == '\'') && cb_string(input, len, out))
			continue ;
		else if ((chr == '\"' || chr == '\''))
		{
			vector_destroy(out);
			return (false);
		}
		chr = (*input)[*len];
		if (chr != '\0' && !vector_push(out, &chr))
			return (false);
		*len += 1;
	}
	return (true);
}

/*
** cb_item (previously cb_unit)
**  THESE DOCS ARE BAD
**  CONTACT ME ON SLACK FOR THIS LOL
**  parses command 'units'
**  a unit is literally text-that-is-not-in-string-quotes
**
**  tl;dr:
**  echo hello -> echo and hello are both units
**  echo "hello" -> echo is a unit, hello is a string
**  "echo" 'hello' -> echo is a string, hello is a string
*/

t_bool	cb_item(
		char **input,
		char **output)
{
	size_t		len;
	t_vector	out;
	char		chr;

	if (!vector_new(&out, sizeof(char)))
		return (false);
	len = 0;
	if (!cb_unit_core(input, &len, &out))
		return (false);
	chr = '\0';
	if (!vector_push(&out, &chr))
		return (false);
	*input += len;
	if (len > 0)
		*output = out.raw;
	else
		vector_destroy(&out);
	return (len > 0);
}
