/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   putnbr_base.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 03:58:29 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/26 00:50:42 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

static int	itocar(unsigned long n, const char *radix, char *out, int g1k)
{
	const t_size	base = ft_strlen(radix);
	int				ret;
	int				commas;

	commas = 0;
	ret = 0;
	if (n == 0)
	{
		out[0] = '0';
		ret = 1;
	}
	while (n != 0)
	{
		if (g1k && ret && (ret - commas) % 3 == 0)
		{
			commas += 1;
			out[ret] = ',';
			ret += 1;
		}
		out[ret] = radix[n % base];
		n /= base;
		ret += 1;
	}
	return (ret);
}

int			putnbr_base(long n, const char *radix, int g1k)
{
	int	res;

	res = 0;
	if (n < 0)
	{
		putchr('-');
		n *= -1;
		res += 1;
	}
	res += putnbr_base_u((unsigned long)n, radix, g1k);
	return (res);
}

int			putnbr_base_u(unsigned long n, const char *radix, int g1k)
{
	char		out[32];
	int			res;
	int			idx;

	res = itocar(n, radix, (char *)out, g1k);
	idx = 0;
	while (idx < res)
	{
		idx += 1;
		putchr(out[res - idx]);
	}
	return (res);
}
