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
#include <stdlib.h>

/*
** this file is essentially unreadable because
** the norm is shit
** all functions have multi-ownership over variables etc
** this part should very VERY much be tested for bugs
*/

static t_bool	push_string_to_vector(
		t_vector *vec,
		char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx] != '\0')
	{
		if (!vector_push(vec, &str[idx]))
			return (false);
		idx += 1;
	}
	return (true);
}

static t_bool	check_variable_from_env(
		char *input,
		size_t *idx,
		t_table *env,
		t_vector *builder)
{
	t_vector	varname;
	char		*value;
	size_t		sidx;

	sidx = *idx + 1;
	if (!vector_new(&varname, sizeof(char)))
		return (false);
	while (ft_isalnum(input[sidx]) || input[sidx] == '_')
	{
		if (!vector_push(&varname, &input[sidx]))
			return (0);
		sidx += 1;
	}
	if (!vector_push(&varname, &input[ft_strlen(input)]))
		return (0);
	*idx = sidx;
	value = table_get(env, varname.raw);
	vector_destroy(&varname);
	if (value != NULL && !push_string_to_vector(builder, value))
		return (0);
	return (1);
}

/*
** because the norm is shit,
** check_variable has partial ownership over t_vector *builder
*/

static int		check_variable(
		char *input,
		size_t *idx,
		t_table *env,
		t_vector *builder)
{
	char		*value;

	if (ft_isalpha(input[*idx + 1]) || input[*idx + 1] == '_')
	{
		if (!check_variable_from_env(input, idx, env, builder))
		{
			vector_destroy(builder);
			return (0);
		}
		return (1);
	}
	else if (input[*idx + 1] == '?')
	{
		value = ft_itoa(g_program_status);
		if (value != NULL && !push_string_to_vector(builder, value))
		{
			free(value);
			vector_destroy(builder);
			return (0);
		}
		free(value);
		*idx += 2;
		return (1);
	}
	return (2);
}

static t_bool	expand_line_core(
		char *input,
		size_t *idx,
		int modes[2],
		void *wtf[2])
{
	while (*idx < ft_strlen(input))
	{
		if (input[*idx] == '$' && modes[0] != '\'')
		{
			modes[1] = check_variable(input, idx, wtf[1], wtf[0]);
			if (modes[1] == 0)
				return (false);
			else if (modes[1] == 1)
				continue ;
		}
		else if (is_string_quote(input[*idx]) && modes[0] == 0)
			modes[0] = input[*idx];
		else if (is_string_quote(input[*idx]) && modes[0] == input[*idx])
			modes[0] = 0;
		else if (input[*idx] == '\\' && modes[0] != STRING_SINGLE_QUOTE)
		{
			if (!vector_push(wtf[0], &input[*idx]))
				return (false);
			*idx += *idx != ft_strlen(input);
		}
		if (!vector_push(wtf[0], &input[*idx]))
			return (false);
		*idx += 1;
	}
	return (true);
}

/*
** expand_line: expand variables within a command group/line
**
** essentially environment variables are replaced with their values
** this also handles program status ($?).
** this parser is string and escape aware.
**
** tl;dr:
** given the environment:
**  BRUH=1234
**  hello=world
**
** the commands are converted as follows:
**  echo $BRUH -> echo 1234
**  echo "hello $hello" -> echo "hello world"
**  echo \$BRUH -> echo $BRUH
**  echo $hello$hello -> echo worldworld
**  echo '$hello' -> echo $hello
*/

t_bool			expand_line(
		char *input,
		t_table *env,
		char **output)
{
	size_t		idx;
	t_vector	builder;
	int			modes[2];
	void		*wtf[2];

	idx = 0;
	modes[0] = 0;
	wtf[0] = &builder;
	wtf[1] = env;
	if (!vector_new(&builder, sizeof(char)))
		return (false);
	if (!expand_line_core(input, &idx, modes, wtf))
	{
		vector_destroy(&builder);
		return (false);
	}
	if (!vector_push(&builder, &input[idx]))
		return (false);
	*output = builder.raw;
	return (true);
}
