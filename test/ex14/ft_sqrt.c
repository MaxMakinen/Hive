/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:53:34 by mmakinen          #+#    #+#             */
/*   Updated: 2021/10/29 17:36:26 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void putnbr(int num)
{
	int x;
	x = 48;
	if (num > 9)
		putnbr(num / 10);
	x += num % 10;
	write (1, &x, 1);
}

int ft_sqrt(int nb)
{
	int	x;

	x = 0;
	while (x * x < nb)
	{
		x++;
		if(x * x == nb)
			return(x);
	}
	return (0);
}

int	main(void)
{
	putnbr(ft_sqrt(4));
	putnbr(ft_sqrt(7));
	putnbr(ft_sqrt(9));
	return (0);
}
