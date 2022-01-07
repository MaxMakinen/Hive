/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strtrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:24:25 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/07 13:57:52 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int main (void)
{
	char *str = "	 	\tbananaman loves peanutbutter sandwiches \n 	";
	char *str2;

	printf("	-=[strtrim test]=-\n\n");
	printf(" -<%s>-\n", str);
	str2 = ft_strtrim(str);
	ft_putstr("-after trim-\n");
	printf(" -<%s>-\n\n", str2);
	return (0);
}
