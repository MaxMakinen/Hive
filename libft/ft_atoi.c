/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:23:44 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/18 14:23:42 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hexval(int c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
}

int	ft_atoi(const char *nptr)
{
	int	value;
	int	negative;

	value = 0;
	negative = 0;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (nptr[0] == '0' && (nptr[1] == 'x' || nptr[1] == 'X'))
	{
		nptr += 2;
		while (*nptr != 0 && ft_isxdigit(*nptr) != 0)
			value = value * 16 + hexval(*nptr++);
	}
	else
	{
		if (nptr[0] == '-' || nptr[0] == '+')
		{
			if (nptr[0] == '-')
				negative = 1;
			nptr++;
		}
		while (*nptr != 0 && (ft_isdigit(*nptr) != 0))
			value = value * 10 + (*nptr++ - '0');
	}
	if (negative == 1)
		value = -value;
	return (value);
}