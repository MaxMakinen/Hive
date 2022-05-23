/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:05:05 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/23 11:03:30 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	int test;
	int	num = 123;
	char	*str = "meep";

	ft_printf("	string test\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%s\n", "meep");
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%s\n", "meep");
	printf("printf test = %d\n\n	~ ~=<:#:>=~ ~\n\n", test);

	ft_printf("	char test\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%c\n", 'M');
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%c\n", 'M');
	printf("printf test = %d\n\n	~ ~=<:#:>=~ ~\n\n", test);

	ft_printf("	width test\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%010s\n", str);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%010s\n", str);
	printf("printf test = %d\n\n	~ ~=<:#:>=~ ~\n\n", test);

	ft_printf("	width + left test\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%-10s$\n", str);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%-10s$\n", str);
	printf("printf test = %d\n\n	~ ~=<:#:>=~ ~\n\n", test);

	ft_printf("	precision test\n\n");
	ft_printf("ft_pf str	= ");
	test = ft_printf("%.10s$\n", str);
	printf("test	= %d\n", test);
	
	test = printf("printf str	= ");
	test = printf("%.10s$\n", str);
	printf("printf test = %d\n\n	~ ~=<:#:>=~ ~\n\n", test);

	ft_printf("	decimal test\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%d\n", num);
	printf("printf test = %d\n\n	~ ~=<:#:>=~ ~\n\n", test);

	return (0);
}
