/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splittest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:00:03 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/08 11:47:43 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void freebie(char **arr)
{
	int c1 = 0;
//	int c2 = 0;

	while (arr[c1] != '\0')
	{
//		while (arr[c1][c2] != '\0')
//		{
//			free(arr[c1][c2]);
//			c2++;
//		}
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
//	char	*str4 = "phone's8help888us88888c8o8m8m8u8n8c8a8t8e8";
	char ** arr;
	char ** arr2;
	char ** arr3;
//	char ** arr4;
	char	d;
	char	d2;
	char	d3;
//	char	d4;
	int		c1 = 0;

	d = 'k';
	arr = ft_strsplit(str2, d);
	while (arr[c1] != '\0')
	{
		ft_putstr(arr[c1]);
		ft_putchar('\n');
		c1++;
	}
	c1 = 0;
	d2 = '*';
	freebie(arr);
	arr2 = ft_strsplit(str, d2);
	while (arr2[c1] != '\0')
	{
		ft_putstr(arr2[c1]);
		ft_putchar('\n');
		c1++;
	}
	c1 = 0;
	d3 = ' ';
	freebie(arr2);
	arr3 = ft_strsplit(str3, d3);
	while (arr3[c1] != '\0')
	{
		ft_putstr(arr3[c1]);
		ft_putchar('\n');
		c1++;
	}
	c1 = 0;
//	d4 = '8';
	freebie(arr3);
/*	arr4 = ft_strsplit(str4, d4);
	while (arr4[c1] != '\0')
	{
		ft_putstr(arr4[c1]);
		ft_putchar('\n');
		c1++;
	}
	freebie(arr4);i*/
	return (0);
}
