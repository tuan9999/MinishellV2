/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_spaced_sign_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/23 22:43:33 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/24 01:07:31 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	flag_spaced_sign(t_flags *flag, char **token, va_list *argp)
{
	(void)argp;
	if (flag->forced_sign != '+')
		flag->forced_sign = ' ';
	(*token)++;
}
