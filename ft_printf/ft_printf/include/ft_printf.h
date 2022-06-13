/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:36:03 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/13 15:45:17 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>

# define ZERO 1
# define LEFT 2
# define PLUS 3
# define SPACE 4
# define MINUS 5
# define PREFIX 6

# define HEX 7
# define NEGATIVE 8
# define SIGNED 9

# define CHAR 10
# define SHORT 11
# define LONG 12
# define LONGLONG 13
# define LONGDOUBLE 14

# define EMPTY 15
# define POINTER 16

# if defined (__linux__)
#  define NIL "(nil)"
#  define NILSIZE 5
#  define LINUX 1
# else
#  define NIL "0x"
#  define NILSIZE 2
#  define LINUX 0
# endif

typedef int	(*t_funcptr)();

typedef union u_input
{
	long long			sll;
	unsigned long long	ull;
	long double			ld;
}	t_input;

typedef struct s_printf
{
	int			fd;
	int			ret;
	int			flags;
	int			width;
	int			precision;
	int			len;
	t_input		input;
	va_list		ap;
	t_funcptr	flag_ptr[5];
	t_funcptr	conv_ptr[11];
}	t_printf;

/*
 * 	Prototypes
 */
int		ft_vdprintf(int fd, const char *format, va_list ap);
int		ft_dprintf(int fd, const char *format, ...);
int		ft_printf(const char *format, ...);

int		zero_padding(const char *format, t_printf *data);
int		left_adjusted(const char *format, t_printf *data);
int		add_prefix(const char *format, t_printf *data);
int		add_plus(const char *format, t_printf *data);
int		add_space(const char *format, t_printf *data);

int		width(const char *format, t_printf *data);
int		precision(const char *format, t_printf *data);
void	check_padding(t_printf *data, int base, int left);
void	padding(t_printf *data);
void	print_precision(t_printf *data);
void	prefix(int base, t_printf *data);

int		print_char(const char **format, t_printf *data);
int		print_string(const char **format, t_printf *data);
int		print_decimal(const char **format, t_printf *data);
int		print_hexadecimal(const char **format, t_printf *data);
int		print_octal(const char **format, t_printf *data);
int		print_pointer(const char **format, t_printf *data);
int		print_unsigned_int(const char **format, t_printf *data);
int		print_percentage(const char **format, t_printf *data);
int		print_float(const char *format, t_printf *data);

int		parse(const char *format, t_printf *data);
void	get_number(t_printf *data);
void	get_float(t_printf *data);

void	ft_ulltoa_base_fd(t_printf *data, unsigned long long num, int base);
int		ft_bit(int step);

#endif
