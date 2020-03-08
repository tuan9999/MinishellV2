/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpattij <dpattij@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 07:13:19 by dpattij           #+#    #+#             */
/*   Updated: 2020/01/21 08:22:45 by dpattij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

static t_bool	cb_command_core(
		char **input,
		t_vector *args,
		t_command_pair *out,
		char *tmp)
{
	if (!vector_push(args, &tmp))
	{
		vector_destroy(args);
		free(out->command);
		free(tmp);
		return (false);
	}
	else
		take_while(input, NULL, is_literal_space);
	return (true);
}

t_bool			cb_command(
		char **input,
		t_command_pair *output)
{
	t_vector		args;
	t_command_pair	out;
	char			*tmp;

	if (!vector_new(&args, sizeof(char *)))
		return (false);
	take_while(input, NULL, is_literal_space);
	if (!cb_item(input, &out.command))
		return (false);
	if (!vector_push(&args, &out.command))
	{
		vector_destroy(&args);
		free(out.command);
		return (false);
	}
	take_while(input, NULL, is_literal_space);
	while (cb_item(input, &tmp))
		if (!cb_command_core(input, &args, &out, tmp))
			return (false);
	out.args = args;
	*output = out;
	return (true);
}
