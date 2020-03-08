/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/22 02:42:51 by anonymous      #+#    #+#                */
/*   Updated: 2019/11/25 23:19:43 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

t_size	max_usize(t_size lhs, t_size rhs)
{
	return (lhs > rhs ? lhs : rhs);
}

t_size	min_usize(t_size lhs, t_size rhs)
{
	return (lhs > rhs ? rhs : lhs);
}

long	abs_long(long n)
{
	return (n >= 0 ? n : -n);
}

int		count_thousands(long n)
{
	int	thousands;

	thousands = 0;
	while (n >= 1000)
	{
		thousands += 1;
		n /= 1000;
	}
	return (thousands);
}
