/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isalnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:26:45 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/07 14:38:43 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int  i = -1;

	printf("\n	-=[Isalnum test]=-\n\n");
	printf("	~While loop -1 -> 255~\n\n");

	while (i < 256)
	{
		if (ft_isalnum(i) != isalnum (i))
		{
			printf("ft_isalnum %d	: %d\n", i, ft_isalnum(i));
			printf("isalnum %d	: %d\n", i, isalnum(i));
		}
		i++;
	}
	return (0);
}
