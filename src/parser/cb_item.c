/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_item.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpattij <dpattij@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 07:05:28 by dpattij           #+#    #+#             */
/*   Updated: 2020/01/23 13:52:52 by dpattij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_bool	cb_string_core(
		char **input,
		size_t *len,
		t_vector *out)
{
	char chr;

	chr = (*input)[*len];
	if (chr == '\\' && **input != '\'')
	{
		if (is_escapable((*input)[*len + 1]))
		{
			*len += 1;
			chr = (*input)[*len];
		}
		else if ((*input)[*len + 1] != '\0')
		{
			if (!vector_push(out, &chr))
				return (false);
			*len += 1;
			chr = (*input)[*len];
		}
		else
		{
			vector_destroy(out);
			return (false);
		}
	}
	return (!(chr != '\0' && !vector_push(out, &chr)));
}

t_bool	cb_string(
		char **input,
		char **output)
{
	size_t		len;
	t_vector	out;
	char		chr;

	if (!vector_new(&out, sizeof(char)))
		return (false);
	if (**input != '\'' && **input != '\"')
	{
		vector_destroy(&out);
		return (false);
	}
	len = 1;
	while ((*input)[len] != **input)
	{
		if (!cb_string_core(input, &len, &out))
			return (false);
		len += 1;
	}
	chr = '\0';
	if (!vector_push(&out, &chr))
		return (false);
	*input += len + 1;
	*output = out.raw;
	return (true);
}

t_bool	cb_unit_core(
		char **input,
		size_t *len,
		t_vector *out)
{
	char chr;

	while (is_not_control((*input)[*len]) && (*input)[*len] != '\0')
	{
		chr = (*input)[*len];
		if (chr == '\\')
		{
			if ((*input)[*len + 1] != '\0')
			{
				*len += 1;
				chr = (*input)[*len];
			}
			else
			{
				vector_destroy(out);
				return (false);
			}
		}
		if (chr != '\0' && !vector_push(out, &chr))
			return (false);
		*len += 1;
	}
	return (true);
}

t_bool	cb_unit(
		char **input,
		char **output)
{
	size_t		len;
	t_vector	out;
	char		chr;

	if (!vector_new(&out, sizeof(char)))
		return (false);
	len = 0;
	if (!cb_unit_core(input, &len, &out))
		return (false);
	chr = '\0';
	if (!vector_push(&out, &chr))
		return (false);
	*input += len;
	if (len > 0)
		*output = out.raw;
	else
		vector_destroy(&out);
	return (len > 0);
}

t_bool	cb_item(
		char **input,
		char **output)
{
	return (cb_string(input, output) || cb_unit(input, output));
}
