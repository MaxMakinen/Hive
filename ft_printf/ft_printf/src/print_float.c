/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:29:09 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/10 12:31:55 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_pow(size_t num, size_t pow)
{
	size_t	temp;

	if (pow == 0)
		return (0);
	temp = num;
	while (pow > 0)
	{
		num *= temp;
		pow--;
	}
	return (num);
}

void	putnbr(size_t n, t_printf *data)
{
	size_t	num;

	if (n > 9)
		putnbr(n / 10, data);
	num = (n % 10) + '0';
	data->ret += write(data->fd, &num, 1);
}

size_t	get_precision(t_printf *data)
{
	size_t	precision;

	if (data->precision == -1)
		data->precision = 6;
	if (data->precision == 0)
		precision = 0;
	else
		precision = ft_pow(10, data->precision);
	return (precision);
}

size_t	get_decimal(t_printf *data, size_t num, size_t precision)
{
	size_t	decimal;

	decimal = (size_t)((data->input.ld - \
				(long double)num) * (long double)precision);
	if (decimal % 10 > 4)
		decimal += 10;
	if (data->flags & ft_bit(NEGATIVE))
		data->ret += write(data->fd, "-", 1);
	return (decimal);
}

int	print_float(const char *format, t_printf *data)
{
	size_t	num;
	size_t	decimal;
	size_t	precision;
	int		number;

	(void)format;
	get_float(data);
	precision = get_precision(data);
	num = (size_t)data->input.ld;
	decimal = get_decimal(data, num, precision);
	putnbr(num, data);
	if (precision != 0)
	{
		data->ret += write(1, ".", 1);
	}
	precision /= 10;
	while (precision > 1)
	{
		number = ((decimal / precision) % 10) + '0';
		data->ret += write(1, &number, 1);
		precision /= 10;
	}
	return (1);
}
