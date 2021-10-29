/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:03:09 by mmakinen          #+#    #+#             */
/*   Updated: 2021/10/29 17:14:09 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putnbr(int num)
{
	int x = 48;

	if (num > 9)
		ft_putnbr(num / 10);
	x += (num % 10);
	write(1, &x, 1);
}

int ft_recursive_factorial(int nb)
{
	if (nb < 0 || nb > 12)
		return (0);
	if (nb == 0 || nb == 1)
		return (1);
	return (nb * ft_recursive_factorial(nb-1));
}

int main(void)
{
	ft_putnbr(ft_recursive_factorial(4));

	return (0);
}
