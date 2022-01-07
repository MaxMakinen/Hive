/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ispunct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:18:01 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/07 10:01:44 by mmakinen         ###   ########.fr       */
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

	printf("\n	-=[ispunct test]=-\n\n");
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
