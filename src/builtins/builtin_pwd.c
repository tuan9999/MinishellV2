/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpattij <dpattij@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 06:02:44 by dpattij           #+#    #+#             */
/*   Updated: 2020/01/27 12:07:14 by dpattij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ministd.h>

int	pwd_main(
		int argc,
		char **argv)
{
	char	*directory;

	(void)argc;
	(void)argv;
	directory = getcwd(NULL, 0);
	if (directory == NULL)
	{
		ft_perror("failed to get directory");
		return (0);
	}
	ft_printf("%s\n", directory);
	free(directory);
	return (0);
}
