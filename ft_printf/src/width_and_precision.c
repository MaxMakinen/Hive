/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 09:54:13 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/20 12:31:00 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	width(const char *format, t_printf *data)
{
	int	len;

	len = 0;
	data->width = ft_atoi(format);
	while (ft_isdigit(*format))
	{
		format++;
		len++;
	}
	return (len);
}

int	precision(const char *format, t_printf *data)
{
	int	len;

	len = 1;
	format++;
	data->precision = ft_atoi(format);
	while (ft_isdigit(*format))
	{
		format++;
		len++;
	}
	return (len);
}
