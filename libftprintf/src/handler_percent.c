/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handler_percent.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 02:16:20 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/23 23:12:56 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

static void		padding(t_size length, char padder)
{
	t_size	idx;

	idx = 1;
	while (idx < length)
	{
		ft_putchar_fd(padder, 1);
		idx += 1;
	}
}

int				handler_percent(t_flags flag, va_list *argp, t_size *written)
{
	(void)argp;
	*written += flag.width > 1 ? flag.width : 1;
	if (flag.flags & FLAG_LEFT_JUSTIFY)
	{
		ft_putchar_fd('%', 1);
		padding(flag.width, ' ');
	}
	else
	{
		padding(flag.width, flag.flags & FLAG_ZERO_PADDING ? '0' : ' ');
		ft_putchar_fd('%', 1);
	}
	return (1);
}
