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
#include <stdlib.h>

static void		cleanup_args(t_vector *self)
{
	char	*item;

	while (vector_pop(self, &item))
		free(item);
}

static t_bool	cb_command_core(
		char **input,
		t_vector *args,
		t_command_pair *out,
		char *tmp)
{
	if (!vector_push(args, &tmp))
	{
		free(out->command);
		free(tmp);
		return (false);
	}
	else
		take_while(input, NULL, is_literal_space);
	return (true);
}

/*
** cb_command: parse a command and its arguments
**  essentially "expect a list of units/strings"
**  it does not place it directly on the instruction stack
**  instead it returns a t_command_pair used as operand to OP_COMMAND...
**  ... (i think)
*/

t_bool			cb_command(
		char **input,
		t_command_pair *output)
{
	t_vector		args;
	t_command_pair	out;
	char			*tmp;

	if (!vector_new_dtor(&args, sizeof(char *), cleanup_args))
		return (false);
	take_while(input, NULL, is_literal_space);
	if (!cb_item(input, &out.command))
		return (false);
	if (!vector_push(&args, &out.command))
	{
		free(out.command);
		return (false);
	}
	take_while(input, NULL, is_literal_space);
	while (cb_item(input, &tmp))
		if (!cb_command_core(input, &args, &out, tmp))
			return (false);
	out.args = args;
	*output = out;
	return (true);
}
