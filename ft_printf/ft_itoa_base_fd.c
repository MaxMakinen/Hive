/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:55:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/09 12:54:25 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>

static int	get_len(long num, int base, int *neg)
{
	int	len;
	int size;

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

static void	prefix(int base, int neg, int fd)
{
	if (base != 10)
	{
		write(fd, "0", 1);
		if (base == 16)
			write(fd, "x", 1);
		else if (base == 8)
			write(fd, "o", 1);
		else if (base == 2)
			write(fd, "b", 1);
	}
	else if (neg == 1)
		write(fd, "-", 1);
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

#include <stdio.h>

void	ft_itoa_base_fd(int num, int base, int fd)
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
	len = get_len(temp, base, &neg);
	prefix(base, neg, fd);
	while (len >= base)
	{
		printf("len : %d\n", len);
		step = key[temp / len];
		write(fd, &step, 1);
		len /= base;
	}
}
