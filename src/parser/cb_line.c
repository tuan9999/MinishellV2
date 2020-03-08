/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpattij <dpattij@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 07:21:28 by dpattij           #+#    #+#             */
/*   Updated: 2020/01/23 14:09:46 by dpattij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

/*
** warning:
** this function DOES modify t_vector *instructions,
** even if it fails!
** therefore the exception handler for parse_line should
**    call the destructor on its contents as well.
*/

static void		destroy_instruction(t_instruction instruction)
{
	char	*tmp;

	free(instruction.operand.pair.command);
	while (vector_pop(&instruction.operand.pair.args, &tmp))
		free(tmp);
	vector_destroy(&instruction.operand.pair.args);
}

static t_bool	parse_op_and_com(
		char **input,
		t_vector *instructions,
		t_bool *success)
{
	t_instruction	instruction;

	*success = **input == '\0';
	while (cb_operation(input, &instruction))
	{
		*success = true;
		if (!vector_push(instructions, &instruction))
		{
			free(instruction.operand.filename);
			return (false);
		}
		if (cb_command(input, &instruction.operand.pair))
		{
			instruction.opcode = OP_COMMAND;
			if (!vector_push(instructions, &instruction))
				destroy_instruction(instruction);
		}
		else if (instruction.opcode == OP_PIPE)
			return (false);
	}
	return (true);
}

t_bool			parse_line(
		char **input,
		t_vector *instructions)
{
	t_instruction	instruction;
	t_bool			success;

	take_while(input, NULL, is_literal_space);
	if (cb_command(input, &instruction.operand.pair))
	{
		instruction.opcode = OP_COMMAND;
		if (!vector_push(instructions, &instruction))
		{
			destroy_instruction(instruction);
			return (false);
		}
		if (!parse_op_and_com(input, instructions, &success) || !success)
			return (false);
		instruction.opcode = OP_CALL;
		if (!vector_push(instructions, &instruction))
		{
			destroy_instruction(instruction);
			return (false);
		}
	}
	return (true);
}
