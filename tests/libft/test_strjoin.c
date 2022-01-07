/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:41:09 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/07 14:43:22 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int main (int argc, char **argv)
{
		if (argc == 2 || argc > 3)
	{
		ft_putstr("Need two strings to join\n");
		return (1);
	}
	char	*mlem;
	char	*mlom;

	if (argc == 1)
	{
		mlem = "Eat my shorts. ";
		mlom = "D'oh!";
	}
	else
	{
		mlem = argv[1];
		mlom = argv[2];
	}
	printf("	-=[strjoin test]=-\n\n");
	printf("-<%s>-\n-<%s>-\n", mlem, mlom);
	printf("-<%s>-\n",ft_strjoin(mlem, mlom));
	printf("\n");
	return (0);
}
