/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:57:37 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/05 16:06:26 by mmakinen         ###   ########.fr       */
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
		n *= (-1);
		*neg = 1;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		neg;
	char	*str;

	neg = 0;
	len = len_tester(n, &neg);
	str = (char *)malloc(sizeof(str) * (len + 1));
	if (str == 0)
		return (NULL);
	str[len] = '\0';
	if (neg == 1)
		str[0] = '-';
	while (len > neg)
	{
		len--;
		str[len] = 48 + (n % 10);
		n /= 10;
	}
	return (str);
}
