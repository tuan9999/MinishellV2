/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_leftjustify.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/23 22:45:43 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/24 01:07:17 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void		flag_leftjustify(t_flags *flag, char **token, va_list *argp)
{
	(void)argp;
	flag->flags |= FLAG_LEFT_JUSTIFY;
	(*token)++;
}
