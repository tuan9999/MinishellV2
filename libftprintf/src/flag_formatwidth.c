/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_formatwidth.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/24 01:09:31 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/24 01:12:32 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	flag_formatwidth(t_flags *flag, char **token, va_list *argp)
{
	t_size	width;

	(void)argp;
	width = 0;
	while (ft_isdigit(**token))
	{
		width = 10 * width + (**token - '0');
		(*token)++;
	}
	flag->width = width;
}
