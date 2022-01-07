/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:00:03 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/07 15:32:18 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void freebie(char **arr)
{
	int c1 = 0;

	while (arr[c1])
	{
		free(arr[c1]);
		c1++;
	}
	free(arr);
}

int	main(void)
{
	char	*str = "**eat*my*********shorts*****banana***";
	char	*str2 = "mykdogkbitkme!";
	char	*str3 = " why are we doing this?  ";
	char	*str4 = "phone's8help888us88888c8o8m8m8u8n8i8c8a8t8e8";
	char ** arr;
	char ** arr2;
	char ** arr3;
	char ** arr4;
	char	d = '\0';
	char	d2 = '*';
	char	d3 = ' ';
	char	d4 = '8';
	char	d5 = 'k';
	int		c1 = 0;

	printf("\n	-=[strsplit test]=-\n\n");
	arr = ft_strsplit(str2, d);
	while (arr[c1])
	{
		ft_putstr(arr[c1]);
		ft_putchar('\n');
		c1++;
	}
	c1 = 0;
	freebie(arr);
	arr = ft_strsplit(str2, d5);
	while (arr[c1])
	{
		ft_putstr(arr[c1]);
		ft_putchar('\n');
		c1++;
	}
	c1 = 0;
	freebie(arr);
	arr2 = ft_strsplit(str, d2);
	while (arr2[c1])
	{
		ft_putstr(arr2[c1]);
		ft_putchar('\n');
		c1++;
	}
	c1 = 0;
	freebie(arr2);
	arr3 = ft_strsplit(str3, d3);
	while (arr3[c1])
	{
		ft_putstr(arr3[c1]);
		ft_putchar('\n');
		c1++;
	}
	c1 = 0;
	freebie(arr3);
	arr4 = ft_strsplit(str4, d4);
	while (arr4[c1])
	{
		ft_putstr(arr4[c1]);
		ft_putchar('\n');
		c1++;
	}
	freebie(arr4);
	printf("\n");
	return (0);
}
