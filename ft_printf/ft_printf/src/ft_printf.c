/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:40:29 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/13 15:39:17 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vdprintf(1, format, ap);
	va_end(ap);
	return (ret);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (ret);
}

static void	reset_data(t_printf *data)
{
	data->flags = 0;
	data->width = 0;
	data->precision = -1;
}

static void	prep_data(t_printf *data)
{
	data->flags = 0;
	data->ret = 0;
	data->width = 0;
	data->precision = -1;
	data->flag_ptr[0] = &zero_padding;
	data->flag_ptr[1] = &left_adjusted;
	data->flag_ptr[2] = &add_plus;
	data->flag_ptr[3] = &add_space;
	data->flag_ptr[4] = &add_prefix;
	data->conv_ptr[0] = &print_char;
	data->conv_ptr[1] = &print_string;
	data->conv_ptr[2] = &print_decimal;
	data->conv_ptr[3] = &print_hexadecimal;
	data->conv_ptr[4] = &print_hexadecimal;
	data->conv_ptr[5] = &print_octal;
	data->conv_ptr[6] = &print_unsigned_int;
	data->conv_ptr[7] = &print_pointer;
	data->conv_ptr[8] = &print_decimal;
	data->conv_ptr[9] = &print_float;
	data->conv_ptr[10] = &print_percentage;
}

int	ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_printf	data;
	int			steps;

	data.fd = fd;
	va_copy(data.ap, ap);
	prep_data(&data);
	while (*format)
	{
		if (*format == '%')
		{
			steps = parse(format, &data);
			if (steps == -1)
				return (-1);
			else
				format += steps;
			reset_data(&data);
		}
		else
			data.ret += write(fd, format, 1);
		format++;
	}
	va_end(data.ap);
	return (data.ret);
}
