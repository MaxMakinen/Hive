/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:17:08 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/18 13:39:25 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_itoa(int num)
{
	long	nbr = num;
	long	temp;
	long	temp2;
	int	neg;
	int	len;
	char			*str;

	neg = 0;
	len = 0;
	if (nbr == 0)
		return ("0");
	if (nbr < 0)
	{
		neg = 1;
		temp = (long)(nbr * -1);
	}
	else
		temp = nbr;
	temp2 = temp;
	while (temp2 > 0)
	{
		temp2 /= 10;
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
	//	printf("len = %d\ntemp = %d\n", len, temp);
		str[(len + neg - 1)] = (temp % 10) + '0';
		temp /= 10;
		len--;
	}
	if (neg)
		str[0] = '-';
	return (str);
}

int main(void)
{
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(1));
	printf("%s\n", ft_itoa(-1));
	printf("%s\n", ft_itoa(INT_MAX));
	printf("%s\n", ft_itoa(INT_MIN));
	printf("%s\n", ft_itoa(420));
}
	
