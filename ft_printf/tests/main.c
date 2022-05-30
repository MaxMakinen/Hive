/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:05:05 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/30 14:42:11 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>                                                             
#include <signal.h>  

int	main(void)
{
	int test;
	int	num = 123;
	char	*str = "meep";

	ft_printf("	~ ~=<: string test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%s\n", "meep");
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%s\n", "meep");
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: char test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%c\n", 'M');
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%c\n", 'M');
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: width test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%10s\n", str);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%10s\n", str);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: width + left test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%-10s$\n", str);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%-10s$\n", str);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: precision test :>=~ ~\n\n");
	ft_printf("ft_pf str	= ");
	test = ft_printf("%.10s$\n", str);
	printf("test	= %d\n", test);
	
	test = printf("printf str	= ");
	test = printf("%.10s$\n", str);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: decimal test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%d\n", num);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: decimal + width test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%5d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%5d\n", num);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: decimal + precision test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%.5d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%.5d\n", num);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: decimal + width + precision test :>=~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%10.5d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%10.5d\n", num);
	printf("test	= %d\n", test);
	
	ft_printf("ft_pf	= ");
	test = ft_printf("%5.10d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%5.10d\n", num);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: hexadecimal test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%x\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%x\n", num);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: HEXAdecimal test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%X\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%X\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%5X\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%5X\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%.5X\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%.5X\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%2.5X\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%2.5X\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%#X\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%#X\n", num);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: octal test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%o\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%o\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%5o\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%5o\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%.5o\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%.5o\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%#o\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%#o\n", num);
	printf("printf test = %d\n", test);

	int	*pnum;
	pnum = &num;
	ft_printf("	~ ~=<: pointer test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%p\n", pnum);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%p\n", pnum);
	printf("printf test = %d\n", test);

	pnum = NULL;

	ft_printf("ft_pf	= ");
	test = ft_printf("%p\n", pnum);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%p\n", pnum);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: plus test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%+d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%+d\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%+.5d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%+.5d\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%+2.5d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%+2.5d\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%+5d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%+5d\n", num);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: negative test :>=~ ~\n\n");
	num = -num;
	ft_printf("ft_pf	= ");
	test = ft_printf("%+d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%+d\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%+.5d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%+.5d\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%+2.5d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%+2.5d\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%+5d\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%+5d\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%x\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%x\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%.5x\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%.5x\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%2.5x\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%2.5x\n", num);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%5x\n", num);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%5x\n", num);
	printf("printf test = %d\n", test);

	unsigned int unum = 420;
	ft_printf("	~ ~=<: unsigned int decimal test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%u\n", unum);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%u\n", unum);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: unsigned int decimal + width test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%5u\n", unum);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%5u\n", unum);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: unsigned int decimal + precision test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%.5u\n", unum);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%.5u\n", unum);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: unsigned int decimal + width + precision test :>=~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%10.5u\n", unum);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%10.5u\n", unum);
	printf("test	= %d\n", test);
	
	ft_printf("ft_pf	= ");
	test = ft_printf("%5.10u\n", unum);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%5.10u\n", unum);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: print NULL string test :>=~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("NULL %s\n", NULL);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("NULL %s\n", NULL);
	printf("test	= %d\n", test);
	
	ft_printf("	~ ~=<: pointer test :>=~ ~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%p\n", 1);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%p\n", 1);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%p\n", 15);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%p\n", 15);
	printf("printf test = %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%p\n", 0);
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%p\n", 0);
	printf("printf test = %d\n", test);

	ft_printf("	~ ~=<: print %% test :>=~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%%\n");
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%%\n");
	printf("test	= %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%\n");
	printf("test	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%\n");
	printf("test	= %d\n", test);

	ft_printf("ft_pf	= ");
	test = ft_printf("%");
	printf("\ntest	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%");
	printf("\ntest	= %d\n", test);

	ft_printf("	~ ~=<: print ld test :>=~\n\n");
	ft_printf("ft_pf	= ");
	test = ft_printf("%ld", (long)INT_MAX + 1);
	printf("\ntest	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%ld", (long)INT_MAX + 1);
	printf("\ntest	= %d\n", test);
	
	ft_printf("ft_pf	= ");
	test = ft_printf("%ld", LONG_MAX);
	printf("\ntest	= %d\n", test);
	
	test = printf("printf	= ");
	test = printf("%ld", LONG_MAX);
	printf("\ntest	= %d\n", test);
	
	return (0);
}
