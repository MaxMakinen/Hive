/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:55:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/25 12:31:53 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"
#include <unistd.h>

static int	get_len(long num, int base, t_printf *data)
{
	int	len;
	int	size;

	len = 0;
	size = base;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		len++;
		num /= base;
	}
	data->precision -= len;
	data->width -= len;
	if (data->precision >= 0)
		data->width -= data->precision;
	while (len-- > 2)
		size *= base;
	return (size);
}

static void	prefix(int base, int neg, t_printf *data)
{
	if (data->flags & PREFIX)
	{
		if (base != 10)
		{
			data->ret += write(data->fd, "0", 1);
			if (base == 16 && data->flags & HEX)
				data->ret += write(data->fd, "X", 1);
			if (base == 16 && !(data->flags & HEX))
				data->ret += write(data->fd, "x", 1);
			else if (base == 2)
				data->ret += write(data->fd, "b", 1);
		}
		else if (neg == 1)
			data->ret += write(data->fd, "-", 1);
	}
}

static void	check_neg(long *num, int *neg, int base)
{
	if (*num < 0)
	{
		*num *= -1;
		if (base == 10)
			*neg = 1;
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

void	check_padding(t_printf *data)
{
	if (data->precision > -1 && data->flags & ZERO)
		data->flags ^= ZERO;
	if (!(data->flags & LEFT))
		padding(data);
	else
		data->flags ^= LEFT;
	while (data->precision > 0)
	{
		data->ret += write(1, "0", 1);
		data->precision--;
	}
}

void	ft_itoa_base_fd(t_printf *data, int num, int base)
{
	int		len;
	int		neg;
	long	temp;
	char	*key;
	char	step;

	if (data->flags & HEX)
		key = "0123456789ABCDEF";
	else
		key = "0123456789abcdef";
	temp = num;
	neg = 0;
	check_neg(&temp, &neg, base);
	len = get_len(temp, base, data);
	check_padding(data);
	prefix(base, neg, data);
	while (len > 0)
	{
		step = key[((temp / len) % base)];
		data->ret += write(data->fd, &step, 1);
		len /= base;
	}
	check_padding(data);
}

static u_int64_t	u_get_len(u_int64_t num, int base, t_printf *data)
{
	u_int64_t	len;
	u_int64_t	size;

	len = 0;
	size = base;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		len++;
		num /= base;
	}
	data->precision -= len;
	data->width -= len;
	if (data->precision >= 0)
		data->width -= data->precision;
	while (len-- > 2)
		size *= base;
	return (size);
}

static void	u_prefix(int base, t_printf *data)
{
	if (data->flags & PREFIX)
	{
		if (base != 10)
		{
			data->ret += write(data->fd, "0", 1);
			if (base == 16 && data->flags & HEX)
				data->ret += write(data->fd, "X", 1);
			if (base == 16 && !(data->flags & HEX))
				data->ret += write(data->fd, "x", 1);
			else if (base == 2)
				data->ret += write(data->fd, "b", 1);
		}
	}
}

void	ft_ulltoa_base_fd(t_printf *data, u_int64_t num, int base)
{
	u_int64_t		len;
	char	*key;
	char	step;

	if (data->flags & HEX)
		key = "0123456789ABCDEF";
	else
		key = "0123456789abcdef";
	len = u_get_len(num, base, data);
	check_padding(data);
	u_prefix(base, data);
	while (len > 0)
	{
		step = key[((num / len) % base)];
		data->ret += write(data->fd, &step, 1);
		len /= base;
	}
	check_padding(data);
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
		write(1, key[temp], 1);
		num = num >> 4;
	}

}
*/
