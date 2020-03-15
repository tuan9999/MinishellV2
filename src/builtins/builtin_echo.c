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

#include <ft_printf.h>
#include <libft.h>

int		echo_main(
		int argc,
		char **argv)
{
	int		idx;
	int		trail;

	idx = 1;
	trail = 0;
	if (argc > 1)
		trail = ft_strncmp(argv[1], "-n", 3) == 0;
	idx += trail;
	while (idx < argc)
	{
		ft_printf("%s", argv[idx]);
		idx += 1;
		if (idx != argc)
			ft_printf(" ");
	}
	if (!trail)
		ft_printf("\n");
	return (0);
}
