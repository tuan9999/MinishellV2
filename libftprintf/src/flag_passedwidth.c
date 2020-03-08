/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_passedwidth.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/23 22:46:25 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/25 01:02:53 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "printf.h"

void		flag_passedwidth(t_flags *flag, char **token, va_list *argp)
{
	int		width;

	width = va_arg(*argp, int);
	if (width < 0)
	{
		flag->flags |= FLAG_LEFT_JUSTIFY;
		width *= -1;
	}
	flag->flags |= FLAG_WIDTHARG_SET;
	flag->width = width;
	(*token)++;
}
