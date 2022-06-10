/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_padding.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:43:37 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/10 10:33:09 by mmakinen         ###   ########.fr       */
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
