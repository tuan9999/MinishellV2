/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_operation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpattij <dpattij@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 07:33:22 by dpattij           #+#    #+#             */
/*   Updated: 2020/01/21 07:59:23 by dpattij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_bool		cb_operation(
		char **input,
		t_instruction *operation)
{
	t_instruction	tmp;

	if (**input == '|')
		tmp.opcode = OP_PIPE;
	else if (**input == '<')
		tmp.opcode = OP_READ;
	else if (**input == '>')
	{
		tmp.opcode = (*input)[1] == '>' ? OP_APPEND : OP_WRITE;
		if ((*input)[1] == '>')
			*input += 1;
	}
	else
		return (false);
	*input += 1;
	take_while(input, NULL, is_literal_space);
	if (tmp.opcode == OP_WRITE || tmp.opcode == OP_READ
		|| tmp.opcode == OP_APPEND)
		if (!cb_item(input, &tmp.operand.filename))
			return (false);
	*operation = tmp;
	return (true);
}
