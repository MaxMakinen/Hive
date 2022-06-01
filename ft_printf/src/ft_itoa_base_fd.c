/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:55:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/01 10:43:39 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long	get_len(long long num, int base, t_printf *data)
{
	int			len;
	long long	size;

	len = 0;
	size = 1;
	if (num < 0)
	{
		num /= base;
		num = -num;
		len++;
	}
	while (num > 0)
	{
		len++;
		num /= base;
	}
	data->precision -= len;
	data->width -= len + ((data->flags & NEGATIVE) || (data->flags & PLUS));
	if (data->precision >= 0)
		data->width -= data->precision;
	while (len-- > 1)
		size *= base;
	return (size);
}

static void	prefix(int base, t_printf *data)
{
	if (base != 10)
	{
		if (data->flags & PREFIX)
		{
			data->ret += write(data->fd, "0", 1);
			if (base == 16 && data->flags & HEX)
				data->ret += write(data->fd, "X", 1);
			if (base == 16 && !(data->flags & HEX))
				data->ret += write(data->fd, "x", 1);
		}
	}
	if (base == 10)
	{
		if (!(data->flags & NEGATIVE) && data->flags & PLUS)
			data->ret += write(data->fd, "+", 1);
		if (data->flags & NEGATIVE)
			data->ret += write(data->fd, "-", 1);
	}
}

static void	check_neg(long long num, t_printf *data, int base)
{
	if (num < 0)
	{
		if (base == 10)
			data->flags |= NEGATIVE;
	}
}

// I'm not currently using thid bugger
int	ft_divmod(long long *num, int base)
{
	int mod;

	mod = *num % base;
	*num /= base;
	return (mod);
}

void	print_precision(t_printf *data)
{
	while (data->precision > 0)
	{
		data->ret += write(data->fd, "0", 1);
		data->precision--;
	}
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

void	ft_lltoa_base_fd(t_printf *data, long long num, int base)
{
	long long	len;
	char	*key;
	int	step;

	if (data->flags & HEX)
		key = "0123456789ABCDEF";
	else
		key = "0123456789abcdef";
	check_neg(num, data, base);
	len = get_len(num, base, data);
	check_padding(data, base, 0);
	while (len > 0)
	{
		if (data->flags & NEGATIVE)
			step = (-((num / len) % base));
		else
			step = ((num / len) % base);
		data->ret += write(data->fd, &(key[step]), 1);
		len /= base;
	}
	check_padding(data, base, 1);
}

static unsigned long long	u_get_len(unsigned long long num, int base, t_printf *data)
{
	unsigned long long	len;
	unsigned long long	size;

	len = 0 + (num == 0);
	size = 1;
	while (num > 0)
	{
		len++;
		num /= base;
	}
	data->precision -= len;
	data->width -= len;
	if (data->flags & PREFIX)
		data->width -= (base == 8) + (2 * (base == 16));
	if (data->precision >= 0)
		data->width -= data->precision;
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
	check_padding(data, base, 0);
	while (len > 0)
	{
		step = key[((num / len) % base)];
		data->ret += write(data->fd, &step, 1);
		len /= base;
	}
	check_padding(data, base, 1);
}
/*
int	lltoa_base_fd(t_printf *data, long long num, int base)
{
	int		len;
	int		temp;
	int		hex;
	char	neg;
	long long templl;
	char	*key;

	key = "0123456789abcdef";
	temp = 0;
	neg = 0;
	while (checkthings)
	{
		hex = num & 0xF;
		temp += hex % base;
		write(data->fd, key[temp], 1);
		num = num >> 4;
	}

}
*/
