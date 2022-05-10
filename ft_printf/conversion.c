/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:00:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/09 12:55:18 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	conversion(int fd, **const char format, va_list *ap, int *ret)
{
	int count;

	count = 1;
	*format++;
	if (**format == conv_id[i]) //conv_id is array of flags to identify desired function pointer
		conv_func[i](fd, format, ap, ret); //conv func = array of function pointers
	
}

void	output_char(int fd, **const char format, va_list *ap, int *ret)
{
	char	c;

	c = va_arg(*ap, char);
	*ret += write(fd, &c, 1);
}

void	output_string(int fd, **const char format, va_list *ap, int *ret)
{
	char	*s;

	s = va_arg(*ap, *char);
	*ret += write(fd, s, ft_strlen(s));
}

void	output_decimal(int fd, **const char format, va_list *ap, int *ret)
{
	int	num;

	num = va_arg(*ap, int);
}
void	output_octal(int fd, **const char format, va_list *ap, int *ret)
void	output_hex(int fd, **const char format, va_list *ap, int *ret)
void	output_float(int fd, **const char format, va_list *ap, int *ret)
