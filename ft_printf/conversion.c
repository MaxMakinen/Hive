/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:00:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/23 10:59:36 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(const char **format, t_printf *data)
{
	int	c;

	c = va_arg(data->ap, int);
	data->ret += write(data->fd, &c, 1);
	return (1);
}

void padding(t_printf *data, int width)
{
	char	padding;

	if (!(data->flags & LEFT) && data->flags & ZERO)
		padding = '0';
	else
		padding = ' ';
	while (width > 0)
	{
		data->ret += write(data->fd, &padding, 1);
		width--;
	}
}

int	print_string(const char **format, t_printf *data)
{
	char	*s;
	int		len;
	int		width;

	s = va_arg(data->ap, char*);
	len = ft_strlen(s);
	width = data->width - len;
	if (data->flags & ZERO)
		data->flags = data->flags ^ ZERO;
	if (width > 0 && !(data->flags & LEFT))
		padding(data, width);
	data->ret += write(data->fd, s, len);
	if (width > 0 && data->flags & LEFT)
		padding(data, width);
	return (1);
}

int	print_decimal(const char **format, t_printf *data)
{
	int num;
	int	len;

	len = 1;
	num = va_arg(data->ap, int);
	ft_itoa_base_fd(data, num, 10);
	return (len);
}
/*
void	output_octal(int fd, const char **format, va_list *ap, int *ret)
{
	int	num;

	num = va_arg(*ap, int);
	ft_itoa_base_fd(num, 8, fd);
}

void	output_hex(int fd, const char **format, va_list *ap, int *ret)
{
	int	num;

	num = va_arg(*ap, int);
	ft_itoa_base_fd(num, 16, fd);
}
//void	output_float(int fd, const char **format, va_list *ap, int *ret)

*/
