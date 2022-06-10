/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:00:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/10 10:31:49 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(const char **format, t_printf *data)
{
	char	c;

	(void)format;
	c = va_arg(data->ap, int);
	data->width -= 1;
	data->flags &= ~(ft_bit(ZERO));
	if (data->width > 0 && !(data->flags & ft_bit(LEFT)))
		padding(data);
	data->ret += write(data->fd, &c, 1);
	if (data->width > 0 && data->flags & ft_bit(LEFT))
		padding(data);
	return (1);
}

int	print_string(const char **format, t_printf *data)
{
	char	*s;
	int		len;

	(void)format;
	s = (char *)va_arg(data->ap, char *);
	if (s == 0)
		s = "(null)";
	len = ft_strlen(s);
	if (data->precision > -1 && data->precision < len)
		len = data->precision;
	data->width = data->width - len;
	data->flags &= ~(ft_bit(ZERO));
	if (data->width > 0 && !(data->flags & ft_bit(LEFT)))
		padding(data);
	data->ret += write(data->fd, s, len);
	if (data->width > 0 && data->flags & ft_bit(LEFT))
		padding(data);
	return (1);
}

int	print_decimal(const char **format, t_printf *data)
{
	(void)format;
	if (data->precision > -1)
		data->flags &= ~(ft_bit(ZERO));
	get_number(data);
	ft_ulltoa_base_fd(data, data->input.ull, 10);
	return (1);
}

int	print_percentage(const char **format, t_printf *data)
{
	(void)format;
	data->width -= 1;
	if (data->width > 0 && !(data->flags & ft_bit(LEFT)))
		padding(data);
	data->ret += write(data->fd, "%", 1);
	if (data->width > 0 && data->flags & ft_bit(LEFT))
		padding(data);
	return (1);
}
