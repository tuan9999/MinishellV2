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

#include <unistd.h>
#include <stdio.h>

int	read_char(char *out)
{
	static char	buffer[512];
	static int	head = 0;
	static int	max;

	if (head == 0)
	{
		max = read(STDIN_FILENO, buffer, 512);
		if (max == -1)
			return (0);
	}
	*out = max == 0 ? EOF : buffer[head];
	if (max != 0)
		head += 1;
	if (head == max)
		head = 0;
	return (1);
}
