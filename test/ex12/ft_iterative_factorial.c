/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:10:53 by mmakinen          #+#    #+#             */
/*   Updated: 2021/10/29 16:53:49 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int num)
{
	if (num > 9)
		ft_putnbr(num / 10);
	ft_putchar(48 + (num % 10));
}

int	ft_iterative_factorial(int nb)
{
	int	x;
	int counter;

	counter = 1;
	x = 1;
	if (nb == 1 || nb == 0)
		return (1);
	if (nb < 0 || nb > 12)
		return (0);
	while (counter <= nb)
	{
		x *= counter;
		counter++;
	}
	return (x);
}

int main (void)
{
	ft_putnbr(ft_iterative_factorial(4));

	return (0);
}
