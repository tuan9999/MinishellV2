/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 01:19:25 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/25 23:08:02 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define BASE_10 "0123456789"
# define BASE_16LOW "0123456789abcdef"
# define BASE_16UP "0123456789ABCDEF"
# define FLAG_ZERO_PADDING (char)0x1
# define FLAG_LEFT_JUSTIFY (char)0x2
# define FLAG_PRECISION_SET (char)0x4
# define FLAG_WIDTHARG_SET (char)0x8
# define FLAG_ALTERNATIVE (char)0x10
# define FLAG_GROUPEDBY1K (char)0x20

typedef struct	s_flags
{
	char	flags;
	char	forced_sign;
	t_size	width;
	t_size	precision;
}				t_flags;

typedef int		(*t_spec_function)(t_flags, va_list *, t_size *);
typedef void	(*t_flag_function)(t_flags *, char **, va_list *);

struct			s_spec_info
{
	char			specifier;
	t_spec_function	handler;
};

struct			s_flag_info
{
	char			flag;
	t_flag_function	handler;
};

int				ft_printf(const char *format, ...);
t_size			max_usize(t_size lhs, t_size rhs);
t_size			min_usize(t_size lhs, t_size rhs);
long			abs_long(long n);
int				putnbr_base(long n, const char *radix, int g1k);
int				putnbr_base_u(unsigned long n, const char *radix, int g1k);
int				number_length(long n, unsigned int base);
int				number_length_u(unsigned long n, unsigned int base);
int				putchr(char c);
int				count_thousands(long n);

/*
** Specifier handlers
*/

int				handler_percent(t_flags flag, va_list *argp, t_size *written);
int				handler_char(t_flags flag, va_list *argp, t_size *written);
int				handler_string(t_flags flag, va_list *argp, t_size *written);
int				handler_pointer(t_flags flag, va_list *argp, t_size *written);
int				handler_int(t_flags flag, va_list *argp, t_size *written);
int				handler_uint(t_flags flag, va_list *argp, t_size *written);
int				handler_uint_hex(t_flags flag, va_list *argp, t_size *written);
int				handler_uint_hex_upper(
	t_flags flag, va_list *argp, t_size *written);

/*
** Flag handlers
*/

void			flag_zeropadding(t_flags *flag, char **token, va_list *argp);
void			flag_leftjustify(t_flags *flag, char **token, va_list *argp);
void			flag_doprecision(t_flags *flag, char **token, va_list *argp);
void			flag_passedwidth(t_flags *flag, char **token, va_list *argp);
void			flag_formatwidth(t_flags *flag, char **token, va_list *argp);

# ifdef IS_BONUS

void			flag_spaced_sign(t_flags *flag, char **token, va_list *argp);
void			flag_always_sign(t_flags *flag, char **token, va_list *argp);
void			flag_alternative(t_flags *flag, char **token, va_list *argp);
void			flag_groupedby1k(t_flags *flag, char **token, va_list *argp);

# endif

extern const struct s_spec_info	g_specifiers[];
extern const struct s_flag_info	g_flags[];

#endif
