/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 08:42:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/10 11:03:16 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_length(const char **format, t_printf *data)
{
	if (**format == 'h')
	{
		*format += 1;
		if (**format == 'h')
		{
			data->flags |= ft_bit(CHAR);
			*format += 1;
		}
		else
			data->flags |= ft_bit(SHORT);
	}
	else if (**format == 'l')
	{
		*format += 1;
		if (**format == 'l')
		{
			data->flags |= ft_bit(LONGLONG);
			*format += 1;
		}
		else
			data->flags |= ft_bit(LONG);
	}
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

int	parse(const char *format, t_printf *data)
{
	const char	*mem;
	char		*flags;
	char		*conversion;
	int			selection;

	format++;
	mem = format;
	flags = "0-+ #";
	conversion = "csdxXoupif%";
	selection = 0;
	if (*format == 0)
		return (0);
	while (flags[selection] != '\0')
	{
		if (*format == flags[selection])
		{
			format += data->flag_ptr[selection](format, data);
			selection = 0;
			continue ;
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
			data->flags |= ft_bit(HEX);
		if (*format == 'd' || *format == 'i')
			data->flags |= ft_bit(SIGNED);
		if (*format == conversion[selection])
		{
			format += data->conv_ptr[selection](format, data);
			break ;
		}
		selection++;
	}
	return (format - mem);
}
