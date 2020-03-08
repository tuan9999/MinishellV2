/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   putchr.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/24 02:22:26 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/28 16:02:53 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <unistd.h>

int		putchr(char c)
{
	write(1, &c, 1);
	return (1);
}
