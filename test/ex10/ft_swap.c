/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 14:54:54 by mmakinen          #+#    #+#             */
/*   Updated: 2021/10/29 15:10:32 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_swap(int *a, int *b)
{
	int	x;

	x = *a;
	*a = *b;
	*b = x;
}

int	main(void)
{
	int	x = 42;
	int	y = 65;

	ft_putchar (x);
	ft_putchar (y);
	ft_swap (&x, &y);
	ft_putchar (x);
	ft_putchar (y);
	return (0);
}
