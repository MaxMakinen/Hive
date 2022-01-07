/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:12:59 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/07 13:58:02 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
int main (int argc, char **argv)
{
	char *mlem;
	if (argc > 2)
		printf("Give one string to measure");
	if (argc == 1)
		mlem = "Bananacrackers01231889	 \n";
	else
		mlem = argv[1];
	printf("	-=[strlen test]=-\n\n");
	printf("ft_strlen : %li\n", ft_strlen(mlem));
	printf("strlen : %li\n\n", strlen(mlem));
	return (0);
}

