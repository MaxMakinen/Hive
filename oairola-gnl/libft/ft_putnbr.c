/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:16:56 by oairola           #+#    #+#             */
/*   Updated: 2021/12/02 14:53:31 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putlongnbr(long int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		ft_putlongnbr(-n);
	}
	else if (n / 10 != 0)
	{
		ft_putlongnbr(n / 10);
		ft_putlongnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}

void	ft_putnbr(int n)
{
	long int	a;

	a = (long int)n;
	ft_putlongnbr(a);
}
