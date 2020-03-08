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

#include <runtime_loop.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>

t_vector	g_running_processes;

void	signal_handler(int signal)
{
	int		pid;
	size_t	idx;

	idx = g_running_processes.size;
	while (idx > 0)
	{
		idx -= 1;
		vector_get(&g_running_processes, idx, &pid);
		kill(pid, signal);
	}
}

void	global_ctor(void)
{
	if (!vector_new(&g_running_processes, sizeof(int)))
	{
		ft_perror("failed to initialize process stack");
		exit(1);
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

int		load_env(t_table *env)
{
	size_t	idx;
	size_t	location;
	size_t	length;
	char	*var[2];

	idx = 0;
	while (environ[idx] != NULL)
	{
		location = 0;
		while (environ[idx][location] != '=')
			location += 1;
		length = ft_strlen(environ[idx]);
		var[0] = ft_substr(environ[idx], 0, location);
		var[1] = ft_substr(environ[idx], location + 1, location - length);
		if (var[0] == NULL || var[1] == NULL)
		{
			free(var[0]);
			free(var[1]);
			return (0);
		}
		if (!table_insert(env, var[0], var[1]))
			return (0);
		idx += 1;
	}
	return (1);
}

int		main(void)
{
	t_table	env;

	if (!table_new(&env))
	{
		ft_perror("failed to initialize environment");
		exit(1);
	}
	if (!load_env(&env))
	{
		ft_perror("failed to copy environment");
		exit(1);
	}
	global_ctor();
	runtime_loop(&env);
	return (0);
}
