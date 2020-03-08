/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpattij <dpattij@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:26:13 by dpattij           #+#    #+#             */
/*   Updated: 2020/01/31 23:17:15 by dpattij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_printf.h>

int	exit_main(
		int argc,
		char **argv)
{
	(void)argc;
	(void)argv;
	ft_printf("exit\n");
	exit(0);
}
