/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_always_sign_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/22 20:29:54 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/24 01:07:09 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	flag_always_sign(t_flags *flag, char **token, va_list *argp)
{
	(void)argp;
	flag->forced_sign = '+';
	(*token)++;
}
