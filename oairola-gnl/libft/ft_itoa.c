/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:49:18 by oairola           #+#    #+#             */
/*   Updated: 2021/12/13 09:37:35 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	iarrlen(long int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	int			a;
	char		*str;
	long int	c;

	c = (long int)n;
	len = iarrlen(c);
	str = (char *)malloc(sizeof(char) * (len + 2));
	if (str == NULL)
		return (NULL);
	if (c < 0)
	{
		c = -c;
		str[0] = '-';
	}
	a = len;
	while (c / 10 != 0)
	{
		str[len] = (c % 10) + '0';
		c = c / 10;
		len--;
	}
	str[len] = c + '0';
	str[a + 1] = '\0';
	return (str);
}
