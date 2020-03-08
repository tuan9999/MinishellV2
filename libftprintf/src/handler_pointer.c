/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handler_pointer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 02:16:20 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/26 00:46:22 by dpattij       ########   odam.nl         */
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

static int	count_hex_thousand(long n)
{
	int	thousands;

	thousands = 0;
	while (n >= 0x1000)
	{
		thousands += 1;
		n /= 0x1000;
	}
	return (thousands);
}

static void	handle_left_justify(
	t_flags flag,
	unsigned int num_len,
	unsigned long arg,
	t_size *written
)
{
	t_size	adjusted_len;

	if (flag.flags & FLAG_GROUPEDBY1K)
		num_len += count_hex_thousand(abs_long((long)arg));
	adjusted_len = max_usize(num_len, flag.precision);
	ft_putstr_fd("0x", 1);
	*written += 2;
	adjusted_len += 2;
	if (flag.precision > num_len)
		*written += padding(flag.precision - num_len, '0');
	if (flag.flags & FLAG_PRECISION_SET && !flag.precision && arg == 0)
		adjusted_len = 0;
	else
		*written += putnbr_base_u((unsigned long)arg, BASE_16LOW, \
			flag.flags & FLAG_GROUPEDBY1K);
	if (flag.width > adjusted_len)
		*written += padding(flag.width - adjusted_len, ' ');
}

static void	handle_right_justify(
	t_flags flag,
	unsigned int num_len,
	unsigned long arg,
	t_size *written
)
{
	t_size	adjusted_len;

	if (flag.flags & FLAG_GROUPEDBY1K)
		num_len += count_hex_thousand(abs_long((long)arg));
	adjusted_len = max_usize(num_len, flag.precision);
	adjusted_len += 2;
	if (flag.flags & FLAG_PRECISION_SET && !flag.precision && arg == 0)
		adjusted_len = 0;
	if (flag.width > adjusted_len && !(flag.flags & FLAG_ZERO_PADDING))
		*written += padding(flag.width - adjusted_len, \
			flag.flags & FLAG_ZERO_PADDING ? '0' : ' ');
	ft_putstr_fd("0x", 1);
	*written += 2;
	if (flag.flags & FLAG_ZERO_PADDING && flag.width > adjusted_len)
		*written += padding(flag.width - adjusted_len, '0');
	if (flag.precision > num_len)
		*written += padding(flag.precision - num_len, '0');
	if (flag.flags & FLAG_PRECISION_SET && !flag.precision && arg == 0)
		return ;
	*written += putnbr_base_u((unsigned long)arg, BASE_16LOW, \
			flag.flags & FLAG_GROUPEDBY1K);
}

int			handler_pointer(t_flags flag, va_list *argp, t_size *written)
{
	void			*arg;
	unsigned int	num_len;

	arg = va_arg(*argp, void *);
	num_len = number_length((unsigned long)arg, 16);
	if (flag.flags & FLAG_PRECISION_SET)
		flag.flags &= ~FLAG_ZERO_PADDING;
	if (flag.flags & FLAG_LEFT_JUSTIFY)
		handle_left_justify(flag, num_len, (unsigned long)arg, written);
	else
		handle_right_justify(flag, num_len, (unsigned long)arg, written);
	return (1);
}
