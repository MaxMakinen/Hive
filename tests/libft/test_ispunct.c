/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:18:01 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/06 20:40:53 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	int x = -200;
	int y;
	int z;

	while (x < 256)
	{
		y = ft_ispunct(x);
		z = ispunct(x);
		if (z != y)
		{
			printf("test : %i %i %i %c\n", x, y, z, x);
		}
		x++;
	}
	return (0);
}
