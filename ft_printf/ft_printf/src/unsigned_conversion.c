/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:40:24 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/10 10:35:09 by mmakinen         ###   ########.fr       */
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
	get_number(data);
	ft_ulltoa_base_fd(data, data->input.ull, 8);
	return (1);
}

int	print_pointer(const char **format, t_printf *data)
{
	unsigned long long	num;
	void				*ptr;

	(void)format;
	if (data->precision > -1)
		data->flags &= ~(ft_bit(ZERO));
	data->flags |= ft_bit(PREFIX);
	data->flags |= ft_bit(POINTER);
	ptr = (va_arg(data->ap, void *));
	num = (unsigned long long)ptr;
	ft_ulltoa_base_fd(data, num, 16);
	return (1);
}
