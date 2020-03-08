/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpattij <dpattij@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:03:44 by dpattij           #+#    #+#             */
/*   Updated: 2020/01/23 14:29:32 by dpattij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <vector.h>
#include <builtin.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <runtime_loop.h>

int			is_builtin(const char *name)
{
	return (ft_strncmp(name, "echo", 5) == 0
	|| ft_strncmp(name, "exit", 5) == 0
	|| ft_strncmp(name, "cd", 3) == 0
	|| ft_strncmp(name, "pwd", 4) == 0
	|| ft_strncmp(name, "env", 4) == 0
	|| ft_strncmp(name, "export", 7) == 0
	|| ft_strncmp(name, "unset", 6) == 0);
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

int			run_builtin(
		t_vector *args,
		t_vector *pipe_stack,
		const int pipes[2],
		t_table *env)
{
	int		pid;
	char	*name;

	(void)vector_get(args, 0, &name);
	if (ft_strncmp(name, "exit", 5) == 0 && pipe_stack->size == 1)
		return (exit_main(0, 0));
	else if (ft_strncmp(name, "cd", 3) == 0 && pipe_stack->size == 1)
		return (cd_main(args->size, (char **)args->raw));
	else if (ft_strncmp(name, "unset", 6) == 0 && pipe_stack->size == 1)
		return (unset_main(args->size, (char **)args->raw, env));
	else if (ft_strncmp(name, "export", 7) == 0 && pipe_stack->size == 1)
		return (export_main(args->size, (char **)args->raw, env));
	pid = fork();
	if (pid == 0)
	{
		build_pipes(pipe_stack, pipes);
		if (ft_strncmp(name, "echo", 5) == 0)
			echo_main(args->size, (char **)args->raw);
		else if (ft_strncmp(name, "pwd", 4) == 0)
			pwd_main(0, 0);
		else if (ft_strncmp(name, "env", 4) == 0)
			env_main(0, 0, env);
		close_pipes(pipes);
		exit(0);
	}
	else if (pid > 0)
		vector_push(&g_running_processes, &pid);
	else
		ft_putendl_fd("failed to setup command", 2);
	close_pipes(pipes);
	return (pid);
}
