/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:55:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/20 17:33:28 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline void	base_ten(t_printf *data)
{
	if (!(data->flags & ft_bit(NEGATIVE)) && data->flags & ft_bit(PLUS))
		data->ret += write(data->fd, "+", 1);
	else if (!(data->flags & ft_bit(NEGATIVE)) && \
			data->flags & ft_bit(SPACE))
		data->ret += write(data->fd, " ", 1);
	if (data->flags & ft_bit(NEGATIVE))
		data->ret += write(data->fd, "-", 1);
}

void	prefix(int base, t_printf *data)
{
	if (base != 10)
	{
		if ((data->flags & ft_bit(PREFIX) && !(data->flags & ft_bit(EMPTY))) \
				|| data->flags & ft_bit(POINTER))
		{
			if ((base == 8 && data->input.ull != 0) && \
					data->precision <= data->len)
				data->ret += write(data->fd, "0", 1);
			if (base == 16 && data->flags & ft_bit(HEX) && \
					data->precision != 0)
				data->ret += write(data->fd, "0X", 2);
			if ((base == 16 && !(data->flags & ft_bit(HEX)) && \
						data->precision != 0) || data->flags & ft_bit(POINTER))
				data->ret += write(data->fd, "0x", 2);
		}
	}
	if (base == 10)
		base_ten(data);
}

void	check_width(t_printf *data, int base)
{
	data->width -= data->len;
	data->width -= ((data->flags & ft_bit(NEGATIVE)) || \
			(data->flags & ft_bit(PLUS)) || data->flags & ft_bit(SPACE));
	if (base == 8 && data->flags & ft_bit(PREFIX) \
			&& data->input.ull != 0 && data->precision <= data->len)
		data->width -= 1;
	if (base == 16 && data->flags & ft_bit(PREFIX) \
			&& (data->input.ull != 0 || data->flags & ft_bit(POINTER)))
		data->width -= 2;
}

static unsigned long long	get_len(unsigned long long num, int base, \
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

	if (data->flags & ft_bit(HEX))
		key = "0123456789ABCDEF";
	else
		key = "0123456789abcdef";
	len = get_len(num, base, data);
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
