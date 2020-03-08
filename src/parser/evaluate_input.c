/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpattij <dpattij@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 21:05:05 by dpattij           #+#    #+#             */
/*   Updated: 2020/02/25 19:12:44 by dpattij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Three step parser:
** seperate (seperate commands with ;)
** loop:
** 	expand (expand variables within a single command)
** 	evaluate (evaluate the comamnd
*/

#include <vector.h>

int		evaluate_input(char *input)
{
	t_vector	commands;

	if (!vector_new(&commands, sizeof(char *)))
		return (1);
	seperate_commands(input, &commands);
	expand_evaluate_loop(&commands);
	return (0);
}
