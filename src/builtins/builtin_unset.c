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

static t_bool	is_starter(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static t_bool	is_ident_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static t_bool	is_valid_identifier(char *str)
{
	size_t	idx;

	if (!is_starter(str[0]))
		return (false);
	idx = 1;
	while (str[idx] != '\0')
	{
		if (!is_ident_char(str[idx]))
			return (false);
		idx += 1;
	}
	return (true);
}

int				unset_main(
		int argc,
		char **argv,
		t_table *env)
{
	int	idx;
	int	errored;

	idx = 0;
	argc -= 1;
	errored = 0;
	while (idx < argc)
	{
		idx += 1;
		if (is_valid_identifier(argv[idx]))
			table_remove(env, ft_strdup(argv[idx]));
		else
		{
			errored = 1;
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd("'", 2);
			ft_putstr_fd(argv[idx], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
	}
	return (errored);
}
