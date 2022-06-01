/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:55:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/01 18:52:47 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long	get_len(long long num, int base, t_printf *data)
{
	int			len;
	long long	size;
	unsigned long long temp;

	size = ((num != 0) || (data->precision != 0));
	len = 0;
	if (num < 0)
	{
		temp = -num;
		data->flags |= NEGATIVE;
	}
	else
		temp = num;
	while (num > 0)
	{
		len++;
		num /= base;
	}
	data->width -= ((data->flags & NEGATIVE) || (data->flags & PLUS) || (data->flags & SPACE));
	while (len-- > 0)
		size *= base;
	return (size);
}

static void	prefix(int base, t_printf *data)
{
	if (base != 10)
	{
		/*
		 * TODO This shit can't be right. Test in different OS.
		 */
		if (base == 8 && (data->precision == 0 && data->flags & PREFIX))
			data->ret += write(data->fd, "0", 1);
		if (data->flags & PREFIX && !(data->flags & EMPTY))
		{
			if (base == 8 && (data->precision != 0))
				data->ret += write(data->fd, "0", 1);
			if (base == 16 && data->flags & HEX && data->precision != 0)
				data->ret += write(data->fd, "0X", 2);
			if (base == 16 && !(data->flags & HEX) && data->precision != 0)
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

static void	check_neg(long long num, t_printf *data, int base)
{
	if (num < 0)
	{
		if (base == 10)
			data->flags |= NEGATIVE;
	}
}

void	print_precision(t_printf *data)
{
	while (data->precision > 0)
	{
		data->ret += write(data->fd, "0", 1);
		data->precision--;
	}
}

void	check_width(t_printf *data, int base)
{
	data->width -= data->len;
	data->precision -= data->len;
	if (data->precision > 0)
	data->width -= data->precision;
	if (base == 8 && data->flags & PREFIX)
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
	check_width(data, base);
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

/*
	data->precision -= len + (num == 0);
	data->width -= len + (num == 0);
	printf("\nlen = %llu, size = %llu\nwidth = %d, prec = %d\n", len, size, data->width, data->precision);
	if (data->precision >= 0)
		data->width -= data->precision;
*/

static unsigned long long	u_get_len(unsigned long long num, int base, t_printf *data)
{
	unsigned long long	len;
	unsigned long long	size;

	size = ((num != 0) || (data->precision != 0));//((num != 0) || (base == 8));
	len = 0;
	while (num > 0)
	{
		len++;
		num /= base;
	}
	data->len = len + (num == 0);
	while (len-- > 0)
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
	if (num == 0)
		data->flags |= EMPTY;
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
