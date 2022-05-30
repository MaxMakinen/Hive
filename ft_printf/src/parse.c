/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 08:42:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/30 14:18:19 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_length(const char **format, t_printf *data)
{
	if (**format == 'h')
	{
		*format += 1;
		if (**format == 'h')
			data->flags |= SHORT;
		else
			data->flags |= CHAR;
	}
	else if (**format == 'l')
	{
		*format += 1;
		if (**format == 'l')
			data->flags |= LONGLONG;
		else
			data->flags |= LONG;
	}
	else if (**format == 'L')
		data->flags |= LONGDOUBLE;
}

int	parse(const char *format, t_printf *data)
{
	const char	*mem;
	char		*flags;
	char		*conversion;
	int			selection;

	format++;
	mem = format;
	flags = "0-+ #";
	conversion = "csdxXoupif";
	selection = 0;
	if (*format == 0)
		return (-1);
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
	get_length(&format, data);
	while (conversion[selection] != '\0')
	{
		if (*format == 'X')
			data->flags |= HEX;
		if (*format == 'd' || *format == 'i')
			data->flags |= SIGNED;
		if (*format == conversion[selection])
		{
			format += data->conv_ptr[selection](format, data);
			break;
		}
		selection++;
	}
	if (format == mem)
		data->ret += write(data->fd, "%", 1);
	return (format - mem);
}
