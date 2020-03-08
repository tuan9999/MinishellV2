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

#include <parser.h>
#include <libft.h>
#include <runtime_loop.h>

static t_bool	is_starter(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static t_bool	is_ident_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

t_bool	expand_line(
		char *input,
		t_table *env,
		char **output)
{
	size_t		idx;
	size_t		sidx;
	char		*value;
	t_vector	builder;
	t_vector	varname;
	char		string_mode;

	idx = 0;
	string_mode = 0;
	if (!vector_new(&builder, sizeof(char)))
		return (false);
	while (idx < ft_strlen(input))
	{
		if (input[idx] == '$' && string_mode != '\'')
		{
			sidx = idx + 1;
			if (!vector_new(&varname, sizeof(char)))
				return (false);
			if (is_starter(input[sidx]))
			{
				while (is_ident_char(input[sidx]))
				{
					if (!vector_push(&varname, &input[sidx]))
						return (false);
					sidx += 1;
				}
				if (!vector_push(&varname, &input[ft_strlen(input)]))
					return (false);
				idx = sidx;
				value = table_get(env, varname.raw);
				if (value != NULL)
				{
					while (*value != '\0')
					{
						if (!vector_push(&builder, value))
						{
							vector_destroy(&varname);
							return (false);
						}
						value += 1;
					}
				}
				vector_destroy(&varname);
				continue ;
			}
			else if (input[sidx] == '?')
			{
				value = ft_itoa(g_program_status);
				if (value != NULL)
				{
					while (*value != '\0')
					{
						if (!vector_push(&builder, value))
							return (false);
						value += 1;
					}
				}
				idx = sidx + 1;
				continue ;
			}
		}
		else if (input[idx] == STRING_DOUBLE_QUOTE || input[idx] == STRING_SINGLE_QUOTE)
		{
			if (string_mode == 0)
				string_mode = input[idx];
			else if (string_mode == input[idx])
				string_mode = 0;
		}
		else if (input[idx] == '\\' && string_mode != STRING_SINGLE_QUOTE)
		{
			if (!vector_push(&builder, &input[idx]))
				return (false);
			idx += 1;
			if (idx == ft_strlen(input))
				idx -= 1;
		}
		if (!vector_push(&builder, &input[idx]))
			return (false);
		idx += 1;
	}
	if (!vector_push(&builder, &input[idx]))
		return (false);
	*output = builder.raw;
	return (true);
}
