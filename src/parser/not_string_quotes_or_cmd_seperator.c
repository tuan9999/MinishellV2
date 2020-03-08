/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_string_quotes_or_cmd_seperator.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpattij <dpattij@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:00:43 by dpattij           #+#    #+#             */
/*   Updated: 2020/02/25 20:00:43 by dpattij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_bool	not_string_quotes_or_cmd_seperator(char c)
{
	return (!(c == CMD_SEPERATOR
	|| c == STRING_SINGLE_QUOTE || c == STRING_DOUBLE_QUOTE));
}
