/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:40:24 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/06 08:41:47 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned_int(const char **format, t_printf *data)
{
	data->flags &= ~(SPACE);
	data->flags &= ~(PLUS);
	return (print_decimal(format, data));
}

int	print_hexadecimal(const char **format, t_printf *data)
{
	(void)format;
	get_number(data);
	ft_ulltoa_base_fd(data, data->input.ull, 16);
	return (1);
}

int	print_octal(const char **format, t_printf *data)
{
	(void)format;
	get_number(data);
	ft_ulltoa_base_fd(data, data->input.ull, 8);
	return (1);
}

int	print_pointer(const char **format, t_printf *data)
{
	unsigned long long	num;
	void				*ptr;

	(void)format;
	data->flags |= PREFIX;
	ptr = (va_arg(data->ap, void *));
	num = (unsigned long long)ptr;
	if (num == 0)
	{
		data->width -= 5;
		if (data->flags & ZERO)
			data->flags = data->flags ^ ZERO;
		if (data->width > 0 && !(data->flags & LEFT))
			padding(data);
		data->ret += write(data->fd, NIL, NILSIZE);
		if (data->width > 0 && data->flags & LEFT)
			padding(data);
	}
	else
		ft_ulltoa_base_fd(data, num, 16);
	return (1);
}
