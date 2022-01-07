/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:24:19 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/07 14:41:18 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char x1[] = "     \t +1958";
	char x2[] = "     \t -1958";
	char x3[] = "     \t +19a58";
	char x4[] = "     \t +1958a";
	char x5[] = "  a   \t +1958";
	char x6[] = " \f \n \r \t \v +1958";
	char x7[] = "     \t -+1958";
	char hex[] = "     \t 0x7A6";
	char x9[] = "     \t 00069";
	char x10[] = "1958";
	char x11[] = "21474836480";
	char x12[] = "-21474836490";

	printf("	-=[atoi test]=-\n\n");
	printf("ft_atoi 1 :	%d \n", ft_atoi(x1));
	printf("atoi 1 :	%d \n", atoi(x1));
	printf("ft_atoi 2 :	%d\n", ft_atoi(x2));
	printf("atoi 2 :	%d \n", atoi(x2));
	printf("ft_atoi 3 :	%d \n", ft_atoi(x3));
	printf("atoi 3 :	%d \n", atoi(x3));
	printf("ft_atoi 4 :	%d \n", ft_atoi(x4));
	printf("atoi 4 :	%d \n", atoi(x4));
	printf("ft_atoi 5 :	%d \n", ft_atoi(x5));
	printf("atoi 5 :	%d \n", atoi(x5));
	printf("ft_atoi 6 :	%d \n", ft_atoi(x6));
	printf("atoi 6 :	%d \n", atoi(x6));
	printf("ft_atoi 7 :	%d \n", ft_atoi(x7));
	printf("atoi 7 :	%d \n", atoi(x7));
	printf("ft_atoi hex : 	%d \n", ft_atoi(hex));
	printf("atoi hex :	%d \n", atoi(hex));
	printf("ft_atoi 9 :	%d \n", ft_atoi(x9));
	printf("atoi 9 :	%d \n", atoi(x9));
	printf("ft_atoi 10 :	%d \n", ft_atoi(x10));
	printf("atoi 10 :	%d \n", atoi(x10));
	printf("ft_atoi beyond MAX_INT :	%d \n", ft_atoi(x11));
	printf("atoi beyond MAX_INT :		%d \n", atoi(x11));
	printf("ft_atoi beyond MIN_INT :	%d \n", ft_atoi(x12));
	printf("atoi beyond MIN_INT :		%d \n\n", atoi(x12));
	return (0);
}
