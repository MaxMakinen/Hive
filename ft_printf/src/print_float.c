/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:29:09 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/20 17:52:46 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

	if (1 / data->input.ld < 0)
		data->flags |= ft_bit(NEGATIVE);
	if (data->precision == -1)
		data->precision = 6;
	if (data->precision == 0)
		precision = 0;
	else
		precision = ft_pow(10, data->precision);
	return (precision);
}

void	rounding(t_printf *data, size_t *num, size_t *decimal)
{
	long double	round;

	round = data->input.ld - (long double)*num;
	if (data->precision == 0)
	{
		if (((round > 0.449f && round < 0.501) && !((*num + 1) % 2)))
			*num += 1;
		else if (round > 0.5)
			*num += 1;
	}
	if ((*decimal % 10 == 5 && (((((*decimal / 10 + 1) % 2) == 0)) || \
				(((*decimal / 10 + 1) % 10) == 1))) || *decimal % 10 > 5)
		*decimal += 10;
}

size_t	get_decimal(t_printf *data, size_t *num, size_t precision)
{
	size_t		decimal;
	size_t		temp;
	size_t		len;

	temp = (size_t)data->input.ld;
	len = 1;
	while (temp > 9)
	{
		temp /= 10;
		len++;
	}
	data->len = len + ((data->flags & ft_bit(PLUS)) > 0 || \
			((data->flags & ft_bit(NEGATIVE)) > 0) || \
			((data->flags & ft_bit(SPACE)) > 0));
	decimal = (size_t)((data->input.ld - \
				(long double)*num) * (long double)precision);
	if (data->precision > 0 || data->flags & ft_bit(PREFIX))
		data->len += 1;
	rounding(data, num, &decimal);
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
	decimal = get_decimal(data, &num, precision);
	float_padding(data, 0);
	putnbr(num, data);
	if (precision != 0 || data->flags & ft_bit(PREFIX))
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
	float_padding(data, 1);
	return (1);
}
