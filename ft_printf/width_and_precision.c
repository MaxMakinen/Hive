/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 09:54:13 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/25 10:59:46 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int	width(const char *format, t_printf *data)
{
	int len;

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
	int len;

	len = 1;
	format++;
	// Change into local while loop, should be faster.
	data->precision = ft_atoi(format);
	while (ft_isdigit(*format))
	{
		format++;
		len++;
	}
	return (len);
}
