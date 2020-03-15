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

/*
** destroy_instruction:
** given an instruction, if the instruction is marked as one that allocates
**  (basically anything that's not CALL or PIPE)
** it will free whatever is allocated and associated with the instruction
**
** warning:
** this function DOES modify t_vector *instructions,
** even if it fails!
** therefore the exception handler for parse_line should
**    call the destructor on its contents as well.
*/

static void		destroy_instruction(t_instruction instruction)
{
	if (instruction.opcode == OP_COMMAND)
		vector_destroy(&instruction.operand.pair.args);
	else if (instruction.opcode != OP_CALL && instruction.opcode != OP_PIPE)
		free(instruction.operand.filename);
}

/*
** clean_instructions:
** destroy all the instructions that have been created so far
**
** because prior to a parser error instructions might've been created
** so we need to free those as well
*/

t_bool			clean_instructions(t_vector *instructions)
{
	t_instruction	out;

	while (vector_pop(instructions, &out))
		destroy_instruction(out);
	return (false);
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

/*
** parse_line:
** takes a line/command group (so, a previously seperated line, aka, no ';')
** and compiles it into instructions
** ReAd tHE vM DOCS fOr More INfo On INStructIOns
**
** the parser is built as a classical & combinator hybrid (spaghetti),
**  mostly using something along the lines of recursive descent
**
** a command group/line is handled as follows (using EBNF, skipping spaces)
** line = command-pair { op_and_com } ;
** op_and_com = operator, command-pair
** command-pair = command { , args } ;
** command = unit | string ;
** args = unit | string ;
** operator = ">" | ">>" | "|" | "<" ;
** unit = anything that's not a string
** string = anything that's in string quotations ("bruh", 'bruh')
*/

t_bool			parse_line(
		char **input,
		t_vector *instructions)
{
	t_instruction	instruction;
	t_bool			success;

	take_while(input, NULL, is_literal_space);
	if (**input == '\0')
		return (true);
	if (cb_command(input, &instruction.operand.pair))
	{
		instruction.opcode = OP_COMMAND;
		if (!vector_push(instructions, &instruction))
			return (clean_instructions(instructions));
		if (!parse_op_and_com(input, instructions, &success) || !success)
			return (clean_instructions(instructions));
		instruction.opcode = OP_CALL;
		if (!vector_push(instructions, &instruction))
		{
			destroy_instruction(instruction);
			return (clean_instructions(instructions));
		}
		return (true);
	}
	return (false);
}
