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
#include <fcntl.h>
#include <stdio.h>

int	handle_op_append(
		t_instruction *instruction,
		t_vm_state *state)
{
	int	pipe_temp[2];

	pipe_temp[0] = open(instruction->operand.filename,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
	pipe_temp[1] = -1;
	if (pipe_temp[0] == -1)
		ft_perror("failed to open file");
	if (!(vector_push(&state->pipestack, &pipe_temp[0])
		&& vector_push(&state->pipestack, &pipe_temp[1])))
		return (0);
	return (1);
}
