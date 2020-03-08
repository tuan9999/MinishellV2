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

#include <builtin.h>
#include <libft.h>
#include <stdlib.h>

static t_bool	is_valid_identifier(char *str)
{
	size_t	idx;

	if (str == NULL)
		return (false);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (false);
	idx = 1;
	while (str[idx] != '\0')
	{
		if (!(ft_isalnum(str[idx]) || str[idx] == '_'))
			return (false);
		idx += 1;
	}
	return (true);
}

static int		free_pair(
		void *a,
		void *b)
{
	free(a);
	free(b);
	return (1);
}

static t_bool	try_set(
		char *str,
		t_table *env)
{
	size_t	location;
	size_t	length;
	char	*var[2];

	location = 0;
	while (str[location] != '=')
		location += 1;
	length = ft_strlen(str);
	var[0] = ft_substr(str, 0, location);
	var[1] = ft_substr(str, location + 1, location - length);
	if (var[0] == NULL || var[1] == NULL)
		return (free_pair(var[0], var[1]));
	if (!table_insert(env, var[0], var[1]))
		return (free_pair(var[0], var[1]));
	if (!is_valid_identifier(var[0]))
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd("'", 2);
		ft_putstr_fd(var[0], 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free_pair(var[0], var[1]);
		return (2);
	}
	return (0);
}

int	export_main(
		int argc,
		char **argv,
		t_table *env)
{
	int	idx;
	int	errored;
	int res;

	idx = 0;
	argc -= 1;
	errored = 0;
	while (idx < argc)
	{
		idx += 1;
		res = try_set(argv[idx], env);
		if (res == 1)
			ft_perror("failed to set variable");
		errored = errored || res != 0;
	}
	return (errored);
}
