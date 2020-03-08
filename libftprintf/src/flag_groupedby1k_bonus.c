/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_groupedby1k_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/24 00:58:41 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/24 01:08:24 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	flag_groupedby1k(t_flags *flag, char **token, va_list *argp)
{
	(void)argp;
	flag->flags |= FLAG_GROUPEDBY1K;
	(*token)++;
}
