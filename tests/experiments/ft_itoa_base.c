/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:17:08 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/18 13:48:50 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_itoa_base(int nbr, int base)
{
	long	num = nbr;
	long	temp;
	long	temp2;
	int		neg;
	int		len;
	char	*str;
	int		digit;

	neg = 0;
	len = 0;
	if (num == 0)
		return ("0");
	if (num < 0)
	{
		if (base == 10)
			neg = 1;
		temp = (num * -1);
	}
	else
		temp = num;
	temp2 = temp;
	while (temp2 > 0)
	{
		temp2 /= base;
		len++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1 + neg));
	while (temp2 < (len + neg))
	{
		str[temp2] = 0;
		temp2 ++;
	}
	while (temp > 0)
	{
		digit = temp % base;
		if (digit > 9)
			str[(len + neg - 1)] = digit + 'A' - 10;
		else
			str[(len + neg - 1)] = digit + '0';
		temp /= base;
		len--;
	}
	if (neg)
		str[0] = '-';
	return (str);
}

int main(void)
{
	printf("%s\n", ft_itoa_base(0, 8));
	printf("%s\n", ft_itoa_base(0, 10));
	printf("%s\n", ft_itoa_base(0, 16));
	printf("%s\n", ft_itoa_base(1, 2));
	printf("%s\n", ft_itoa_base(-1, 2));
	printf("%s\n", ft_itoa_base(INT_MAX, 2));
	printf("%s\n", ft_itoa_base(INT_MIN, 2));
	printf("%s\n", ft_itoa_base(INT_MAX, 10));
	printf("%s\n", ft_itoa_base(INT_MIN, 10));
	printf("%s\n", ft_itoa_base(INT_MAX, 16));
	printf("%s\n", ft_itoa_base(INT_MIN, 16));
	printf("%s\n", ft_itoa_base(420, 2));
	printf("%s\n", ft_itoa_base(420, 8));
	printf("%s\n", ft_itoa_base(420, 10));
	printf("%s\n", ft_itoa_base(420, 16));
}
	
