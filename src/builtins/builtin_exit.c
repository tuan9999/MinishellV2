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

#include <stdlib.h>
#include <ft_printf.h>
#include <ministd.h>
#include <libft.h>
#include <runtime_loop.h>

static t_bool	take_n(const char *str, unsigned char *out)
{
	*out = 0;
	while (*str != '\0' && ft_isdigit(*str))
	{
		*out = *out * 10 + *str - '0';
		str += 1;
	}
	if (*str != '\0')
		return (false);
	return (true);
}

int				exit_main(
		int argc,
		char **argv)
{
	unsigned char	code;

	ft_printf("exit\n");
	if (argc == 1)
		exit(g_program_status);
	if (!take_n(argv[1], &code))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	if (argc > 2)
		ft_putendl_fd("exit: too many arguments", 2);
	else if (argc == 2)
		exit(code);
	return (1);
}
