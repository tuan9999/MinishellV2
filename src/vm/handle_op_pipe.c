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
#include <unistd.h>

int	handle_op_pipe(
	t_instruction *instruction,
	t_vm_state *state)
{
	int	pipe_temp[2];

	(void)instruction;
	if (pipe(pipe_temp) == -1)
	{
		ft_perror("failed to setup pipes");
		return (0);
	}
	if (!(vector_push(&state->pipestack, &pipe_temp[1])
	&& vector_push(&state->pipestack, &pipe_temp[0])))
		return (0);
	return (1);
}
