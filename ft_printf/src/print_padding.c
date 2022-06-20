/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_padding.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:43:37 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/20 17:05:59 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	padding(t_printf *data)
{
	char	padding;
	int		prec;

	if (data->precision - data->len >= 0)
		prec = data->precision - data->len;
	else
		prec = 0;
	if (!(data->flags & ft_bit(LEFT)) && data->flags & ft_bit(ZERO))
		padding = '0';
	else
		padding = ' ';
	while ((data->width - prec) > 0)
	{
		data->ret += write(data->fd, &padding, 1);
		data->width--;
	}
}

void	print_precision(t_printf *data)
{
	int	prec;

	prec = data->precision;
	while ((prec - data->len) > 0)
	{
		data->ret += write(data->fd, "0", 1);
		prec--;
	}
}

void	check_padding(t_printf *data, int base, int left)
{
	if (data->precision > -1 && data->flags & ft_bit(ZERO))
		data->flags &= ~(ft_bit(ZERO));
	if (left && data->flags & ft_bit(LEFT))
		padding(data);
	else if (!left)
	{
		if (data->flags & ft_bit(ZERO) && !(data->flags & ft_bit(LEFT)))
		{
			prefix(base, data);
			padding(data);
		}
		else if (!(data->flags & ft_bit(LEFT)))
		{
			padding(data);
			prefix(base, data);
		}
		else if (data->flags & ft_bit(LEFT))
			prefix(base, data);
		print_precision(data);
	}
}

void	f_padding(t_printf *data)
{
	char	padding;
	int		prec;

	if (data->precision > 0)
		prec = data->precision + data->len;
	else
		prec = data->len;
	if (!(data->flags & ft_bit(LEFT)) && data->flags & ft_bit(ZERO))
		padding = '0';
	else
		padding = ' ';
	while ((data->width - prec) > 0)
	{
		data->ret += write(data->fd, &padding, 1);
		data->width--;
	}
}

void	float_padding(t_printf *data, int left)
{
	if (left == 1 && data->flags & ft_bit(LEFT))
		f_padding(data);
	if (left == 0 && data->flags & ft_bit(ZERO) && \
			!(data->flags & ft_bit(LEFT)))
	{
		prefix(10, data);
		f_padding(data);
	}
	else if (left == 0 && !(data->flags & ft_bit(ZERO)) && \
			!(data->flags & ft_bit(LEFT)))
	{
		f_padding(data);
		prefix(10, data);
	}
	else if (left == 0 && data->flags & ft_bit(LEFT))
	{
		prefix(10, data);
	}
}
