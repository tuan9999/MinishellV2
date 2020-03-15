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
#include <parser.h>
#include <stdlib.h>
#include <ministd.h>

/*
** core loop of the shell,
** consists out of:
** 1. displaying a prompt
** 2. reading a line (taking input)
** 3. evaluating the line (running the 'code' in the line)
*/

int		runtime_loop(t_table *env)
{
	char		*input_buffer;
	int			res;

	while (true)
	{
		if (display_prompt(env) != DISPLAY_PROMPT_SUCCESS)
			break ;
		res = take_input(&input_buffer);
		if (res == TAKE_INPUT_EXIT_CALLED)
			return (RUNTIME_LOOP_EXIT);
		if (res == TAKE_INPUT_READLINE_FAILED)
			break ;
		evaluate_input(input_buffer, env);
		free(input_buffer);
	}
	return (RUNTIME_LOOP_CRASH);
}
