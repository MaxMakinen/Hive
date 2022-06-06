/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:55:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/06 15:01:57 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	prefix(int base, t_printf *data)
{
	if (base != 10)
	{
		/*
		 * TODO This shit can't be right. Test in different OS. 
		 * Turns out this shit is right...
		 * mix into the different checks better.
		 */
		if (base == 8 && data->precision == 0 && data->flags & PREFIX)
			data->ret += write(data->fd, "0", 1);
		if ((data->flags & PREFIX && !(data->flags & EMPTY)) || data->flags & POINTER)
		{
			if (base == 8 && (data->precision < 1))
				data->ret += write(data->fd, "0", 1);
			if (base == 16 && data->flags & HEX && data->precision != 0)
				data->ret += write(data->fd, "0X", 2);
			if ((base == 16 && !(data->flags & HEX) && data->precision != 0) || data->flags & POINTER)
				data->ret += write(data->fd, "0x", 2);
		}
	}
	if (base == 10)
	{
		if (!(data->flags & NEGATIVE) && data->flags & PLUS)
			data->ret += write(data->fd, "+", 1);
		else if (!(data->flags & NEGATIVE) && data->flags & SPACE)
			data->ret += write(data->fd, " ", 1);
		if (data->flags & NEGATIVE)
			data->ret += write(data->fd, "-", 1);
	}
}

void	check_width(t_printf *data, int base)
{
	data->width -= data->len;
	data->width -= ((data->flags & NEGATIVE) || (data->flags & PLUS) || \
			data->flags & SPACE);
	data->precision -= data->len;
	if (data->precision > 0)
		data->width -= data->precision;
	if (base == 8 && data->flags & PREFIX && data->precision < 1)
		data->width -= 1;
	if (base == 16 && data->flags & PREFIX)
		data->width -= 2;
}

void	check_padding(t_printf *data, int base, int left)
{
	if (data->precision > -1 && data->flags & ZERO)
		data->flags &= ~(ZERO);
	if (left && data->flags & LEFT)
		padding(data);
	else if (!left)
	{
		if (data->flags & ZERO && !(data->flags & LEFT))
		{
			prefix(base, data);
			padding(data);
		}
		else if (!(data->flags & LEFT))
		{
			padding(data);
			prefix(base, data);
		}
		else if (data->flags & LEFT)
			prefix(base, data);
		print_precision(data);
	}
}

static unsigned long long	u_get_len(unsigned long long num, int base, \
		t_printf *data)
{
	unsigned long long	len;
	unsigned long long	size;

	size = ((num != 0) || (data->precision != 0));
	len = (num == 0) * (data->precision != 0);
	while (num > 0)
	{
		len++;
		num /= base;
	}
	data->len = (int)len;
	while (len-- > 1)
		size *= base;
	return (size);
}

void	ft_ulltoa_base_fd(t_printf *data, unsigned long long num, int base)
{
	unsigned long long	len;
	char				*key;
	char				step;

	if (data->flags & HEX)
		key = "0123456789ABCDEF";
	else
		key = "0123456789abcdef";
	len = u_get_len(num, base, data);
	check_width(data, base);
	check_padding(data, base, 0);
	while (len > 0)
	{
		step = key[((num / len) % base)];
		data->ret += write(data->fd, &step, 1);
		len /= base;
	}
	check_padding(data, base, 1);
}
