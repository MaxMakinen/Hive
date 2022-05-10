/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:40:29 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/09 15:00:57 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdarg.h"

typedef int *(*funcptr)();			//generic function pointer.
typedef funcptr (*ptrfuncptr)();	//ptr to func returning generic function pointer.

/*
 * printf calls vprintf-> calls vdprintf
 * asprintf calls vasprintf
 */

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vdprintf(1, format, ap);
	va_end(ap);
	return (ret):
}

int	ft_dprintf(int fd ,const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (ret):
}

int	ft_vdprint(int fd, const char *format, va_list ap)
{
	char	*temp;
	char	*read;
	int		ret;

	read = format;
	while (*read)
	{
		if (read* == '%')
			conversion(fd, &read, &ap, &ret);
		if (read* == '\\')
		{
			read++;
			if (!*read)
				break;
		}
		ret += write(fd, read, 1);
		read++;
	}
	return (ret);
}
