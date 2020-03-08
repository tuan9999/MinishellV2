/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_atleast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpattij <dpattij@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 05:51:32 by dpattij           #+#    #+#             */
/*   Updated: 2020/01/16 05:51:36 by dpattij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_bool	skip_atleast(
		char **input,
		char matcher,
		size_t times)
{
	size_t occurs;

	occurs = 0;
	while ((*input)[occurs] == matcher)
		occurs += 1;
	*input += occurs;
	return (occurs >= times);
}
