/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:27:05 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/13 14:50:29 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline void	get_signed(t_printf *data)
{
	if (data->flags & ft_bit(CHAR))
		data->input.sll = (char)va_arg(data->ap, int);
	else if (data->flags & ft_bit(SHORT))
		data->input.sll = (short)va_arg(data->ap, int);
	else if (data->flags & ft_bit(LONG))
		data->input.sll = (long)va_arg(data->ap, long);
	else if (data->flags & ft_bit(LONGLONG))
		data->input.sll = (long long)va_arg(data->ap, long long);
	else
		data->input.sll = (int)va_arg(data->ap, int);
	if (data->input.sll < 0)
	{
		data->input.ull = -data->input.sll;
		data->flags |= ft_bit(NEGATIVE);
	}
	else
		data->input.ull = data->input.sll;
}

void	get_number(t_printf *data)
{
	if (data->flags & ft_bit(SIGNED))
		get_signed(data);
	else
	{
		if (data->flags & ft_bit(CHAR))
			data->input.ull = (unsigned char)va_arg(data->ap, unsigned int);
		else if (data->flags & ft_bit(SHORT))
			data->input.ull = (unsigned short)va_arg(data->ap, unsigned int);
		else if (data->flags & ft_bit(LONG))
			data->input.ull = (unsigned long)va_arg(data->ap, unsigned long);
		else if (data->flags & ft_bit(LONGLONG))
			data->input.ull = \
			(unsigned long long)va_arg(data->ap, unsigned long long);
		else
			data->input.ull = (unsigned int)va_arg(data->ap, unsigned int);
	}
	if (data->input.ull == 0)
		data->flags |= ft_bit(EMPTY);
}

void	get_float(t_printf *data)
{
	if (data->flags & ft_bit(LONGDOUBLE))
		data->input.ld = (long double)va_arg(data->ap, long double);
	else
		data->input.ld = (long double)va_arg(data->ap, double);
	if (data->input.ld < 0 || data->input.ld == -0.0)
	{
		data->flags |= ft_bit(NEGATIVE);
		data->input.ld = -data->input.ld;
	}
}
