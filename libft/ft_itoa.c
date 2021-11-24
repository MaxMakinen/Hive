/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:57:37 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/24 12:53:13 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_tester(int n, int *neg)
{
	int	test;
	int	len;

	len = 1;
	test = n;
	while (test / 10 != 0)
	{
		len++;
		test /= 10;
	}
	if (n < 0)
	{
		len++;
		*neg = 1;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		neg;
	long	num;
	char	*str;

	num = n;
	neg = 0;
	len = len_tester(n, &neg);
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (str == 0)
		return (NULL);
	str[len] = '\0';
	if (neg == 1)
	{
		num = -num;
		str[0] = '-';
	}
	while (len > neg)
	{
		len--;
		str[len] = 48 + (num % 10);
		num /= 10;
	}
	return (str);
}
