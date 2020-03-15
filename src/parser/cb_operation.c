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

/*
** cb_operation:
**  operator rule handler
**  essentially the same as "expect an operator"
**
**  if the following character is NOT an operator,
**  fail the parse.
**  otherwise:
**  if the operator is a file-based operator (READ <, APPEND >>, WRITE >)
**  also expect a filename.
**  if it's just a pipe, tell the parent parser to expect another command.
**  if all prior parses are successful, add the operator as an instruction.
*/

t_bool		cb_operation(
		char **input,
		t_instruction *operation)
{
	t_instruction	tmp;

	if (**input == '|')
		tmp.opcode = OP_PIPE;
	else if (**input == '<')
		tmp.opcode = OP_READ;
	else if (**input == '>')
	{
		tmp.opcode = (*input)[1] == '>' ? OP_APPEND : OP_WRITE;
		if ((*input)[1] == '>')
			*input += 1;
	}
	else
		return (false);
	*input += 1;
	take_while(input, NULL, is_literal_space);
	if (tmp.opcode == OP_WRITE || tmp.opcode == OP_READ
		|| tmp.opcode == OP_APPEND)
		if (!cb_item(input, &tmp.operand.filename))
			return (false);
	*operation = tmp;
	return (true);
}
