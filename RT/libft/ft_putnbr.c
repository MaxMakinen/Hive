/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:52:28 by jjuntune          #+#    #+#             */
/*   Updated: 2021/11/29 13:21:51 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int	nbr;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(1, "-", 1);
			n = n * -1;
		}
		if (n > 9)
		{
			ft_putnbr(n / 10);
			nbr = ((n % 10) + '0');
			write(1, &nbr, 1);
		}
		else if (n < 10)
		{
			nbr = (n + '0');
			write(1, &nbr, 1);
		}
	}
}
