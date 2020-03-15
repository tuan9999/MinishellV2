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

const char	*g_sig_names[22] =
{
	"Bogus signal",
	"Hangup",
	"Interrupt",
	"Quit",
	"Illegal instruction",
	"Trace/BPT trap",
	"Abort trap",
	"EMT trap",
	"Floating point exception",
	"Killed",
	"Bus error",
	"Segmentation fault",
	"Bad system call",
	"Broken pipe",
	"Alarm clock",
	"Terminated",
	"Cputime limit exceeded",
	"Filesize limit exceeded",
	"Virtual timer expired",
	"Profiling timer expired",
	"User defined signal 1",
	"User defined signal 2"
};

int			g_program_status = 0;

/*
** Gets the pipes for a given process. Read vm_execute.c's pipestack
**  distribution explanation for uh, more explanation. :-)
*/

static void	get_pipes(
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

/*
** spawn_process:
**  Create and run a new process given a command pair.
**  Checks whether a command is a builtin or not. If it is a builtin,
**   the builtin command will be executed with priority over a regular command.
*/

static int	spawn_process(
		t_vm_state *state,
		t_command_pair *command,
		int pipe_temp[2])
{
	int		pid;

	if (is_builtin(command->command))
	{
		pid = run_builtin(&command->args, &state->pipestack,
				pipe_temp, state->env);
		g_program_status = pid;
	}
	else
		pid = run_process(&command->args, &state->pipestack, pipe_temp,
				state->env);
	return (pid != -1);
}

/*
** wait_for_processes:
**  Waits for all running processes to end.
**  The status of the 'top'/main process will be set as eventual status.
**  If a (potentially deadly) signal is received, it will print -
**   a signal message (usually a signal name) followed by the signal number.
**  If the process exited normally, the program status ($?) will be set
**  to the exit code of the process.
**  If the signal exited through a signal, the program status ($?) will be
**  set to 128 + the signal number.
*/

static void	wait_for_processes(void)
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
			if (WIFSIGNALED(status))
			{
				status = WTERMSIG(status);
				g_program_status = 128 + status;
				if (status < 23 && status != 2)
					ft_printf("%s: %d\n", g_sig_names[status], status);
				else if (status != 2)
					ft_printf("Unknown Signal: %d\n", status);
			}
			top = 0;
		}
	}
}

int			handle_op_call(
		t_instruction *instruction,
		t_vm_state *state)
{
	size_t			idx;
	int				pipe_temp[2];
	t_command_pair	*command;

	idx = 0;
	(void)instruction;
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
	pipe_temp[0] = -1;
	if (!vector_push(&state->pipestack, &pipe_temp[0]))
		return (0);
	return (1);
}
