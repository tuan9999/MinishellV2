/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handler_uint.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 03:07:08 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/25 23:22:59 by dpattij       ########   odam.nl         */
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
	unsigned int num_len,
	unsigned int arg,
	t_size *written
)
{
	t_size	adjusted_len;

	if (flag.flags & FLAG_GROUPEDBY1K)
		num_len += count_thousands(abs_long((long)arg));
	adjusted_len = max_usize(num_len, flag.precision);
	if (flag.precision > num_len)
		*written += padding(flag.precision - num_len, '0');
	if (flag.flags & FLAG_PRECISION_SET && !flag.precision && arg == 0)
		adjusted_len = 0;
	else
		*written += putnbr_base_u((unsigned long)arg, BASE_10, \
			flag.flags & FLAG_GROUPEDBY1K);
	if (flag.width > adjusted_len)
		*written += padding(flag.width - adjusted_len, ' ');
}

static void	handle_right_justify(
	t_flags flag,
	unsigned int num_len,
	unsigned int arg,
	t_size *written
)
{
	t_size	adjusted_len;

	if (flag.flags & FLAG_GROUPEDBY1K)
		num_len += count_thousands(abs_long((long)arg));
	adjusted_len = max_usize(num_len, flag.precision);
	if (flag.flags & FLAG_PRECISION_SET && !flag.precision && arg == 0)
		adjusted_len = 0;
	if (flag.width > adjusted_len)
		*written += padding(flag.width - adjusted_len, \
			flag.flags & FLAG_ZERO_PADDING ? '0' : ' ');
	if (flag.precision > num_len)
		*written += padding(flag.precision - num_len, '0');
	if (flag.flags & FLAG_PRECISION_SET && !flag.precision && arg == 0)
		return ;
	*written += putnbr_base_u((unsigned long)arg, BASE_10, \
			flag.flags & FLAG_GROUPEDBY1K);
}

int			handler_uint(t_flags flag, va_list *argp, t_size *written)
{
	unsigned int	arg;
	unsigned int	num_len;

	arg = va_arg(*argp, unsigned int);
	num_len = number_length((unsigned long)arg, 10);
	if (flag.flags & FLAG_PRECISION_SET)
		flag.flags &= ~FLAG_ZERO_PADDING;
	if (flag.flags & FLAG_LEFT_JUSTIFY)
		handle_left_justify(flag, num_len, arg, written);
	else
		handle_right_justify(flag, num_len, arg, written);
	return (1);
}
