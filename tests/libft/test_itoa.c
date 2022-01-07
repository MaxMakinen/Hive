/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:42:56 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/07 15:29:06 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#ifndef MAX_INT
# define MAX_INT 2147483647
#endif
#ifndef MIN_INT
# define MIN_INT -2147483648
#endif
int main (void)
{
	char *str;
	int i = 0;
	
	printf("\n	-=[itoa test]=-\n\n");
	printf("	~test 1~\nint 		1988\nft_itoa	:	%s\n",ft_itoa(1988));
	printf("	~test 2~\nint 		-1988\nft_itoa : ");
	str = ft_itoa(-1988);
	printf("	%s\n",str);
	printf("	~test 3~\nMAX_INT		%i\nft_itoa :	%s\n", MAX_INT, ft_itoa(MAX_INT));
	printf("	~test 4~\nMIN_INT		%li\nft_itoa :	%s\n", MIN_INT, ft_itoa(MIN_INT));
	printf("	~test 5~\nMAX_INT + 1	%li\nft_itoa :	%s\n", (MAX_INT+1), ft_itoa(MAX_INT+1));
	printf("	~test 6~\nMIN_INT - 1	%li\nft_itoa :	%s\n", (MIN_INT-1), ft_itoa(MIN_INT-1));
	return (0);
}
