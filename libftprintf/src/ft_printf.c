/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 01:19:09 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/24 03:20:55 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "printf.h"
#include "libft.h"

const struct s_spec_info	g_specifiers[] =
{
	{'c', handler_char},
	{'s', handler_string},
	{'p', handler_pointer},
	{'d', handler_int},
	{'i', handler_int},
	{'u', handler_uint},
	{'x', handler_uint_hex},
	{'X', handler_uint_hex_upper},
	{'%', handler_percent},
	{'\0', NULL}
};

const struct s_flag_info	g_flags[] =
{
	{'-', flag_leftjustify},
	{'0', flag_zeropadding},
	{'.', flag_doprecision},
	{'*', flag_passedwidth},
	{'1', flag_formatwidth},
	{'2', flag_formatwidth},
	{'3', flag_formatwidth},
	{'4', flag_formatwidth},
	{'5', flag_formatwidth},
	{'6', flag_formatwidth},
	{'7', flag_formatwidth},
	{'8', flag_formatwidth},
	{'9', flag_formatwidth},

#ifdef IS_BONUS

	{' ', flag_spaced_sign},
	{'+', flag_always_sign},
	{'#', flag_alternative},
	{'\'', flag_groupedby1k},

#endif

	{'\0', NULL}
};

static t_flags	flag_handler(char **token, va_list *argp)
{
	t_size	idx;
	t_flags	flag;

	flag.flags = 0;
	flag.forced_sign = '\0';
	flag.width = 0;
	flag.precision = 0;
	(*token)++;
	while (1)
	{
		idx = 0;
		while (g_flags[idx].flag != **token && g_flags[idx].handler != NULL)
			idx += 1;
		if (g_flags[idx].handler != NULL)
		{
			g_flags[idx].handler(&flag, token, argp);
			continue ;
		}
		else
			break ;
	}
	return (flag);
}

static int		run_handler(char **token, va_list *argp, t_size *written)
{
	t_size	idx;
	t_flags	flag;

	idx = 0;
	flag = flag_handler(token, argp);
	while (g_specifiers[idx].specifier != **token
	&& g_specifiers[idx].handler != NULL)
		idx += 1;
	if (g_specifiers[idx].handler != NULL)
		g_specifiers[idx].handler(flag, argp, written);
	return (0);
}

int				ft_printf(const char *format, ...)
{
	va_list	argp;
	t_size	written;
	char	*token;

	va_start(argp, format);
	token = (char *)format;
	written = 0;
	while (*token != '\0')
	{
		if (*token == '%')
		{
			run_handler(&token, &argp, &written);
			if (*token == '\0')
				break ;
		}
		else
		{
			ft_putchar_fd(*token, 1);
			written += 1;
		}
		token++;
	}
	va_end(argp);
	return (written);
}
