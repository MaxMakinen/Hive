/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:00:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/30 13:00:04 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(const char **format, t_printf *data)
{
	char c;

	(void)format;
	c = va_arg(data->ap, int);
	data->ret += write(data->fd, &c, 1);
	return (1);
}

void padding(t_printf *data)
{
	char	padding;

	if (!(data->flags & LEFT) && data->flags & ZERO)
		padding = '0';
	else
		padding = ' ';
	while (data->width > 0)
	{
		data->ret += write(data->fd, &padding, 1);
		data->width--;
	}
}

int	print_string(const char **format, t_printf *data)
{
	char	*s;
	int		len;

	(void)format;
	s = (char *)va_arg(data->ap, char*);
	if (s == 0)
		s = "(null)";
	len = ft_strlen(s);
	data->width = data->width - len;
	if (data->flags & ZERO)
		data->flags = data->flags ^ ZERO;
	if (data->width > 0 && !(data->flags & LEFT))
		padding(data);
	data->ret += write(data->fd, s, len);
	if (data->width > 0 && data->flags & LEFT)
		padding(data);
	return (1);
}

int	print_decimal(const char **format, t_printf *data)
{
	(void)format;
	if (data->flags & SIGNED)
	{
		data->input.sll = va_arg(data->ap, int);
		ft_lltoa_base_fd(data, data->input.sll, 10);
	}
	else
	{
		data->input.ull = va_arg(data->ap, unsigned int);
		ft_ulltoa_base_fd(data, data->input.ull, 10);
	}
	return (1);
}

int	print_hexadecimal(const char **format, t_printf *data)
{
	unsigned int num;
	int	len;

	(void)format;
	len = 1;
	num = va_arg(data->ap, unsigned int);
	ft_ulltoa_base_fd(data, num, 16);
	return (len);
}

int	print_octal(const char **format, t_printf *data)
{
	int num;
	int	len;

	(void)format;
	len = 1;
	num = va_arg(data->ap, unsigned int);
	ft_ulltoa_base_fd(data, num, 8);
	return (len);
}

int	print_pointer(const char **format, t_printf *data)
{
	unsigned long long	num;
	void	*ptr;

	(void)format;
	data->flags |= PREFIX;
	ptr = (va_arg(data->ap, void *));
	num = (unsigned long long)ptr;
	if (num == 0)
	{
		data->ret += 5;
		ft_putstr("(nil)");
	}
	else
		ft_ulltoa_base_fd(data, num, 16);
	return (1);
}
