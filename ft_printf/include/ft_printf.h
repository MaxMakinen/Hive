/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:36:03 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/06 09:59:55 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>

typedef int	(*t_funcptr)();

// This union should propably be removed. Don't think it does anything.
typedef union u_input
{
	long long			sll;
	unsigned long long	ull;
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
void	prep_data(t_printf *data);

int		zero_padding(const char *format, t_printf *data);
int		left_adjusted(const char *format, t_printf *data);
int		add_prefix(const char *format, t_printf *data);
int		add_plus(const char *format, t_printf *data);
int		add_space(const char *format, t_printf *data);

int		width(const char *format, t_printf *data);
int		precision(const char *format, t_printf *data);
void	padding(t_printf *data);
void	print_precision(t_printf *data);

int		print_char(const char **format, t_printf *data);
int		print_string(const char **format, t_printf *data);
int		print_decimal(const char **format, t_printf *data);
int		print_hexadecimal(const char **format, t_printf *data);
int		print_octal(const char **format, t_printf *data);
int		print_pointer(const char **format, t_printf *data);
int		print_unsigned_int(const char **format, t_printf *data);
int		print_percentage(const char **format, t_printf *data);

int		parse(const char *format, t_printf *data);
void	get_number(t_printf *data);

void	ft_itoa_base_fd(t_printf *data, int num, int base);
void	ft_lltoa_base_fd(t_printf *data, long long num, int base);
void	ft_ulltoa_base_fd(t_printf *data, unsigned long long num, int base);
int		ft_bit(int step);

/*
 * Replace ft_bit with a Macro
 */

# define ZERO ft_bit(1)
# define LEFT ft_bit(2)
# define PLUS ft_bit(3)
# define SPACE ft_bit(4)
# define MINUS ft_bit(5)
# define PREFIX ft_bit(6)

# define HEX ft_bit(7)
# define NEGATIVE ft_bit(8)
# define SIGNED ft_bit(9)

# define CHAR ft_bit(10)
# define SHORT ft_bit(11)
# define LONG ft_bit(12)
# define LONGLONG ft_bit(13)
# define LONGDOUBLE ft_bit(14)

# define EMPTY ft_bit(15)

# if defined (__linux__)
#  define NIL "(nil)"
#  define NILSIZE 5
# else
#  define NIL "0x0"
#  define NILSIZE 3
# endif

#endif
