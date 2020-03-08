/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_alternative_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/24 00:57:44 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/24 01:07:40 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	flag_alternative(t_flags *flag, char **token, va_list *argp)
{
	(void)argp;
	flag->flags |= FLAG_ALTERNATIVE;
	(*token)++;
}
