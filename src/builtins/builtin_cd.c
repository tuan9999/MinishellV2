/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpattij <dpattij@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 05:18:55 by dpattij           #+#    #+#             */
/*   Updated: 2020/01/16 05:25:57 by dpattij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ministd.h>

int	cd_main(
		int argc,
		char **argv)
{
	if (argc > 1 && chdir(argv[1]) == -1)
	{
		ft_perror("cd");
		return (1);
	}
	return (0);
}
