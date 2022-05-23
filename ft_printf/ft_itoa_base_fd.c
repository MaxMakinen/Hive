/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:55:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/23 11:03:02 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"
#include <unistd.h>

static int	get_len(long num, int base)
{
	int	len;
	int	size;

	len = 0;
	size = base;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		len++;
		num /= base;
	}
	while (len-- > 2)
		size *= base;
	return (size);
}

static void	prefix(int base, int neg, t_printf *data)
{
	if (base != 10)
	{
		data->ret += write(data->fd, "0", 1);
		if (base == 16)
			data->ret += write(data->fd, "x", 1);
		else if (base == 8)
			data->ret += write(data->fd, "o", 1);
		else if (base == 2)
			data->ret += write(data->fd, "b", 1);
	}
	else if (neg == 1)
		data->ret += write(data->fd, "-", 1);
}

static void	check_neg(long *num, int *neg, int base)
{
	if (*num < 0)
	{
		*num *= -1;
		if (base == 10)
			*neg = 1;
	}
}

void	ft_itoa_base_fd(t_printf *data, int num, int base)
{
	int		len;
	int		neg;
	long	temp;
	char	*key;
	char	step;

	key = "0123456789ABCDEF";
	temp = num;
	neg = 0;
	check_neg(&temp, &neg, base);
	len = get_len(temp, base);
	prefix(base, neg, data);
	while (len > 0)
	{
		step = key[((temp / len) % base)];
		data->ret += write(data->fd, &step, 1);
		len /= base;
	}
}
