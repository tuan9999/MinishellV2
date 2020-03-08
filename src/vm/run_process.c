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

#include <table.h>
#include <unistd.h>
#include <libft.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <runtime_loop.h>

static int	null_term_args(t_vector *args)
{
	static const char *null = NULL;

	if (!vector_push(args, &null))
	{
		ft_perror("failed to setup command");
		return (1);
	}
	return (0);
}

static void	build_pipes(
		t_vector *pipe_stack,
		const int pipes[2])
{
	int pipe;

	while (vector_pop(pipe_stack, &pipe))
		if (pipe != pipes[0] && pipe != pipes[1] && pipe != -1)
			close(pipe);
	if (pipes[0] != -1 && dup2(pipes[0], STDIN_FILENO) == -1)
	{
		ft_perror("failed to setup reader pipe");
		exit(1);
	}
	if (pipes[1] != -1 && dup2(pipes[1], STDOUT_FILENO) == -1)
	{
		ft_perror("failed to setup writer pipe");
		exit(1);
	}
}

static void	close_pipes(const int pipes[2])
{
	if (pipes[0] != -1)
		close(pipes[0]);
	if (pipes[1] != -1)
		close(pipes[1]);
}

static void	switch_to_process(
		const char *filename,
		char *const *args,
		t_table *env)
{
	(void)env;
	execvp(filename, args);
}

int			run_process(
		t_vector *args,
		t_vector *pipe_stack,
		const int pipes[2],
		t_table *env)
{
	int		pid;
	char	*cmd;

	(void)vector_get(args, 0, &cmd);
	if (null_term_args(args))
		return (0);
	pid = fork();
	if (pid == 0)
	{
		build_pipes(pipe_stack, pipes);
		switch_to_process(cmd, (char *const *)args->raw, env);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		close_pipes(pipes);
		exit(0);
	}
	else if (pid > 0)
		vector_push(&g_running_processes, &pid);
	else
		ft_perror("failed to setup command");
	close_pipes(pipes);
	return (pid);
}
