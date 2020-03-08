/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_doprecision.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/24 00:36:52 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/28 17:03:25 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void		flag_doprecision(t_flags *flag, char **token, va_list *argp)
{
	int		precision_arg;
	t_size	precision;

	precision = 0;
	precision_arg = 0;
	(*token)++;
	if (**token == '\0')
		return ;
	if (**token == '*')
	{
		(*token)++;
		precision_arg = va_arg(*argp, int);
		if (argp < 0)
			return ;
		flag->precision = (t_size)precision_arg;
	}
	flag->flags |= FLAG_PRECISION_SET;
	while (ft_isdigit(**token))
	{
		precision = 10 * precision + (**token - '0');
		(*token)++;
	}
	if (!precision_arg)
		flag->precision = precision;
}
