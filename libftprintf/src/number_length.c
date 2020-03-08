/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   number_length.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 22:38:55 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/25 19:44:14 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		number_length(long n, unsigned int base)
{
	int	length;

	length = n <= 0;
	while (n != 0)
	{
		length += 1;
		n /= base;
	}
	return (length);
}

int		number_length_u(unsigned long n, unsigned int base)
{
	int	length;

	length = 0;
	while (n != 0)
	{
		length += 1;
		n /= base;
	}
	return (length);
}
