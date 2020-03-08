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
#include <builtin.h>
#include <libft.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ft_printf.h>
#include <runtime_loop.h>

const int	g_no_pipes[2] =
{
	-1,
	-1
};

int			g_program_status = 0;

void	get_pipes(
		t_vm_state *state,
		size_t idx,
		int pipe_temp[2])
{
	int prog_pipe;

	if (vector_get(&state->pipestack, idx * 2, &prog_pipe))
	{
		pipe_temp[0] = prog_pipe;
		if (vector_get(&state->pipestack, idx * 2 + 1, &prog_pipe))
			pipe_temp[1] = prog_pipe;
		else
			pipe_temp[1] = -1;
	}
	else
		ft_memcpy(pipe_temp, g_no_pipes, sizeof(g_no_pipes));
}

int		spawn_process(
		t_vm_state *state,
		t_command_pair *command,
		int pipe_temp[2])
{
	int		pid;
	char	*destructor;

	if (is_builtin(command->command))
	{
		pid = run_builtin(&command->args, &state->pipestack,
				pipe_temp, state->env);
		g_program_status = pid;
	}
	else
		pid = run_process(&command->args, &state->pipestack, pipe_temp,
				state->env);
	while (vector_pop(&command->args, &destructor))
		free(destructor);
	vector_destroy(&command->args);
	return (pid != -1);
}

void	wait_for_processes(void)
{
	int	pid;
	int	status;
	int	top;

	top = 1;
	while (vector_pop(&g_running_processes, &pid))
	{
		waitpid(pid, &status, 0);
		if (top)
		{
			if (WIFEXITED(status))
				g_program_status = WEXITSTATUS(status);
			top = 0;
		}
		if (WIFSIGNALED(status) && WTERMSIG(status) != 2)
			ft_printf("Quit: %d\n", WTERMSIG(status));
	}
}

int		handle_op_call(
		t_instruction *instruction,
		t_vm_state *state)
{
	size_t			idx;
	int				pipe_temp[2];
	t_command_pair	*command;

	idx = 0;
	while (idx < state->callstack.size)
	{
		vector_getr(&state->callstack, idx, (void **)&command);
		get_pipes(state, idx, pipe_temp);
		if (!spawn_process(state, command, pipe_temp))
			return (0);
		idx += 1;
	}
	wait_for_processes();
	vector_destroy(&state->callstack);
	vector_destroy(&state->pipestack);
	if (!(vector_new(&state->pipestack, sizeof(int))
		& vector_new(&state->callstack, sizeof(t_command_pair))))
		return (0);
	instruction->opcode = -1;
	if (!vector_push(&state->pipestack, &instruction->opcode))
		return (0);
	return (1);
}
