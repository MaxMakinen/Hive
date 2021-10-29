/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:39:18 by mmakinen          #+#    #+#             */
/*   Updated: 2021/10/29 15:50:22 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	*div = a/b;
	*mod = a%b;
}

int	main(void)
{
	int x = 66;
	int y = 65;

	ft_putchar(x);
	ft_putchar(y);
	ft_div_mod(12, 2, &x, &y);
	x += 65;
	y += 65;
	ft_putchar(x);
	ft_putchar(y);

	return (0);
}
