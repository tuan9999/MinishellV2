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

#include <vm.h>

t_dispatch_item	g_dispatch_table[7] =
{
	{OP_COMMAND, handle_op_command},
	{OP_CALL, handle_op_call},
	{OP_PIPE, handle_op_pipe},
	{OP_WRITE, handle_op_write},
	{OP_READ, handle_op_read},
	{OP_APPEND, handle_op_append},
	{OP_NOP, NULL},
};

int		execute_opcode(
		t_instruction *instruction,
		t_vm_state *state)
{
	if (g_dispatch_table[instruction->opcode].opcode != OP_NOP)
		return (g_dispatch_table[instruction->opcode].fn(instruction, state));
	return (1);
}

int		destroy_state(t_vm_state *state)
{
	vector_destroy(&state->callstack);
	vector_destroy(&state->pipestack);
	return (0);
}

int		vm_execute(
		t_vector *instructions,
		t_table *env)
{
	t_vm_state		state;
	int				dummy;

	state.env = env;
	dummy = -1;
	if (!(vector_new(&state.pipestack, sizeof(int))
	&& vector_new(&state.callstack, sizeof(t_command_pair))))
		return (destroy_state(&state));
	if (!vector_push(&state.pipestack, &dummy))
		return (destroy_state(&state));
	if (!vector_foreachc(instructions, (int (*)(void *, void *)) execute_opcode,
			&state))
		return (destroy_state(&state));
	destroy_state(&state);
	return (1);
}
