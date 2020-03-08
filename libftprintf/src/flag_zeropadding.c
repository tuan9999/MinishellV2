/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_zeropadding.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/22 20:28:07 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/24 01:07:24 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	flag_zeropadding(t_flags *flag, char **token, va_list *argp)
{
	(void)argp;
	flag->flags |= FLAG_ZERO_PADDING;
	(*token)++;
}
