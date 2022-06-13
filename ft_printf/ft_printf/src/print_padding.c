/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_padding.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:43:37 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/12 15:31:41 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	padding(t_printf *data)
{
	char	padding;

	if (!(data->flags & ft_bit(LEFT)) && data->flags & ft_bit(ZERO))
		padding = '0';
	else
		padding = ' ';
	while (data->width > 0)
	{
		data->ret += write(data->fd, &padding, 1);
		data->width--;
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
