/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:27:05 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/06 08:49:52 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline void	get_signed(t_printf *data)
{
	if (data->flags & CHAR)
		data->input.sll = (char)va_arg(data->ap, int);
	else if (data->flags & SHORT)
		data->input.sll = (short)va_arg(data->ap, int);
	else if (data->flags & LONG)
		data->input.sll = (long)va_arg(data->ap, long);
	else if (data->flags & LONGLONG)
		data->input.sll = (long long)va_arg(data->ap, long long);
	else
		data->input.sll = (int)va_arg(data->ap, int);
	if (data->input.sll < 0)
	{
		data->input.ull = -data->input.sll;
		data->flags |= NEGATIVE;
	}
	else
		data->input.ull = data->input.sll;
}

void	get_number(t_printf *data)
{
	if (data->flags & SIGNED)
		get_signed(data);
	else
	{
		if (data->flags & CHAR)
			data->input.ull = (unsigned char)va_arg(data->ap, unsigned int);
		else if (data->flags & SHORT)
			data->input.ull = (unsigned short)va_arg(data->ap, unsigned int);
		else if (data->flags & LONG)
			data->input.ull = (unsigned long)va_arg(data->ap, unsigned long);
		else if (data->flags & LONGLONG)
			data->input.ull = \
			(unsigned long long)va_arg(data->ap, unsigned long long);
		else
			data->input.ull = (unsigned int)va_arg(data->ap, unsigned int);
	}
}
