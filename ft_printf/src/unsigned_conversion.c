/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:40:24 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/20 17:32:11 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned_int(const char **format, t_printf *data)
{
	data->flags &= ~(ft_bit(SPACE));
	data->flags &= ~(ft_bit(PLUS));
	return (print_decimal(format, data));
}

int	print_hexadecimal(const char **format, t_printf *data)
{
	(void)format;
	if (data->precision > -1)
		data->flags &= ~(ft_bit(ZERO));
	get_number(data);
	ft_ulltoa_base_fd(data, data->input.ull, 16);
	return (1);
}

int	print_octal(const char **format, t_printf *data)
{
	(void)format;
	if (data->precision > -1)
		data->flags &= ~(ft_bit(ZERO));
	if (data->precision == 0 && data->flags & ft_bit(PREFIX))
		data->precision = 1;
	get_number(data);
	ft_ulltoa_base_fd(data, data->input.ull, 8);
	return (1);
}

int	print_pointer(const char **format, t_printf *data)
{
	void				*ptr;

	(void)format;
	if (data->precision > -1)
		data->flags &= ~(ft_bit(ZERO));
	data->flags |= ft_bit(PREFIX);
	data->flags |= ft_bit(POINTER);
	ptr = (va_arg(data->ap, void *));
	data->input.ull = (unsigned long long)ptr;
	ft_ulltoa_base_fd(data, data->input.ull, 16);
	return (1);
}
