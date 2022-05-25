/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 08:42:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/25 16:49:30 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

int	parse(const char *format, t_printf *data)
{
	const char	*mem;
	char		*flags;
	char		*conversion;
	int			selection;

	format++;
	mem = format;
	flags = "0-+ #";
	conversion = "csdxXoup";
	selection = 0;
	if (*format == '%')
	{
		data->ret += write(data->fd, "%", 1);
		return (1);
	}
	while (flags[selection] != '\0')
	{
		if (*format == flags[selection])
		{
			format += data->flag_ptr[selection](format, data);
			selection = 0;
			continue;
		}
		selection++;
	}
	if (ft_isdigit(*format))
		format += width(format, data);
	if (*format == '.')
		format += precision(format, data);
	selection = 0;
	while (conversion[selection] != '\0')
	{
		if (*format == 'X')
			data->flags |= HEX;
		if (*format == 'd')
			data->flags |= SIGNED;
		if (*format == conversion[selection])
		{
			format += data->conv_ptr[selection](format, data);
			break;
		}
		selection++;
	}
	return (format - mem);
}
