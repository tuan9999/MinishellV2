/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handler_string.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 03:07:08 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/24 23:58:51 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

static int	padding(t_size length, char padder)
{
	t_size	idx;

	idx = 0;
	while (idx < length)
	{
		putchr(padder);
		idx += 1;
	}
	return (length);
}

static void	handle_left_justify(
	t_flags flag,
	char *arg,
	t_size len,
	t_size *written
)
{
	t_size	idx;

	idx = 0;
	if (flag.flags & FLAG_PRECISION_SET)
		len = min_usize(len, flag.precision);
	while (idx < len)
	{
		*written += putchr(arg[idx]);
		idx += 1;
	}
	if (flag.width > len)
		*written += padding(flag.width - len, ' ');
}

static void	handle_right_justify(
	t_flags flag,
	char *arg,
	t_size len,
	t_size *written
)
{
	t_size	idx;

	idx = 0;
	if (flag.flags & FLAG_PRECISION_SET)
		len = min_usize(len, flag.precision);
	if (flag.width > len)
		*written += padding(flag.width - len, \
			flag.flags & FLAG_ZERO_PADDING ? '0' : ' ');
	while (idx < len)
	{
		*written += putchr(arg[idx]);
		idx += 1;
	}
}

int			handler_string(t_flags flag, va_list *argp, t_size *written)
{
	char	*arg;

	(void)flag;
	arg = va_arg(*argp, char *);
	if (arg == NULL)
		arg = "(null)";
	if (flag.flags & FLAG_LEFT_JUSTIFY)
		handle_left_justify(flag, arg, ft_strlen(arg), written);
	else
		handle_right_justify(flag, arg, ft_strlen(arg), written);
	return (1);
}
