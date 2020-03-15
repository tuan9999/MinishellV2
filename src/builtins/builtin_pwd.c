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
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ministd.h>

int	pwd_main(
		int argc,
		char **argv)
{
	char	*directory;

	(void)argc;
	(void)argv;
	directory = getcwd(NULL, 0);
	if (directory == NULL)
	{
		ft_perror("failed to get directory");
		return (0);
	}
	ft_printf("%s\n", directory);
	free(directory);
	return (0);
}
