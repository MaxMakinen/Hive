/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 08:42:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/10 14:54:22 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline void	set_long(const char **format, t_printf *data)
{
	data->flags |= ft_bit(LONG);
	if (*(++*format) == 'l')
	{
		data->flags |= ft_bit(LONGLONG);
		*format += 1;
	}
}

void	get_length(const char **format, t_printf *data)
{
	if (**format == 'h')
	{
		data->flags |= ft_bit(SHORT);
		if (*++(*format) == 'h')
		{
			data->flags |= ft_bit(CHAR);
			*format += 1;
		}
	}
	else if (**format == 'l')
		set_long(format, data);
	else if (**format == 'L')
	{
		data->flags |= ft_bit(LONGDOUBLE);
		*format += 1;
	}
	else if (**format == 'j')
	{
		data->flags |= ft_bit(LONGLONG);
		*format += 1;
	}
}

void	set_flags(const char **format, t_printf *data)
{
	char		*flags;
	int			selection;

	selection = 0;
	flags = "0-+ #";
	while (flags[selection] != '\0')
	{
		if (**format == flags[selection])
		{
			*format += data->flag_ptr[selection](format, data);
			selection = 0;
			continue ;
		}
		selection++;
	}
}

void	conversion(const char **format, t_printf *data)
{
	char		*conversion;
	int			selection;

	conversion = "csdxXoupif%";
	selection = 0;
	while (conversion[selection] != '\0')
	{
		if (**format == 'X')
			data->flags |= ft_bit(HEX);
		if (**format == 'd' || **format == 'i')
			data->flags |= ft_bit(SIGNED);
		if (**format == conversion[selection])
		{
			*format += data->conv_ptr[selection](format, data);
			break ;
		}
		selection++;
	}
}

int	parse(const char *format, t_printf *data)
{
	const char	*mem;

	format++;
	mem = format;
	if (*format == 0)
		return (0);
	set_flags(&format, data);
	if (ft_isdigit(*format))
		format += width(format, data);
	if (*format == '.')
		format += precision(format, data);
	get_length(&format, data);
	conversion(&format, data);
	return (format - mem);
}
