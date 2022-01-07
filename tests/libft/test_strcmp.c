/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:40:52 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/07 14:48:23 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int main (int argc, char **argv)
{
	if (argc == 2 || argc > 3)
	{
		ft_putstr("Give two strings to compare\n");
		return (1);
	}
	char	*mlem;
	char	*mlom;
	if (argc == 1)
	{
		mlem = "Bananas";
		mlom = "Bananas";
	}
	else
	{
		mlem = argv[1];
		mlom = argv[2];
	}
	printf("	-=[strcmp test]=-\n\n");
	printf("string 1 : %s\nstring 2 : %s\n", mlem, mlom);
	ft_putstr("ft_strcmp	: ");
	ft_putnbr(ft_strcmp(mlem, mlom));
	ft_putchar('\n');
	printf("strcmp		: %i\n", strcmp(mlem, mlom));
	ft_putstr("ft_strncmp 5	: ");
	ft_putnbr(ft_strncmp(mlem, mlom, 5));
	ft_putchar('\n');
	printf("strncmp	5	: %i\n", strncmp(mlem, mlom, 5));
	ft_putstr("ft_strequ	: ");
	ft_putnbr(ft_strequ(mlem, mlom));
	ft_putstr("\nft_strnequ 5	: ");
	ft_putnbr(ft_strnequ(mlem, mlom, 5));
	ft_putchar('\n');
	if ( argc == 1)
	{
		mlem = "Bananas";
		mlom = "Bonobos";
		printf("\nstring 1 : %s\nstring 2 : %s\n", mlem, mlom);
		printf("ft_strcmp	: %d\n", ft_strcmp(mlem,mlom));
		printf("strcmp		: %i\n", strcmp(mlem, mlom));
		printf("ft_strncmp 5	: %d\n", ft_strncmp(mlem,mlom, 5));
		printf("strncmp	5	: %i\n", strncmp(mlem, mlom, 5));
		printf("ft_strequ	: %d\n", ft_strequ(mlem,mlom));
		printf("ft_strnequ 5	: %d\n", ft_strnequ(mlem,mlom, 5));
		mlem = "Bananas";
		mlom = "Bananabread";
		printf("\nstring 1 : %s\nstring 2 : %s\n", mlem, mlom);
		printf("ft_strcmp	: %d\n", ft_strcmp(mlem,mlom));
		printf("strcmp		: %i\n", strcmp(mlem, mlom));
		printf("ft_strncmp 5	: %d\n", ft_strncmp(mlem,mlom, 5));
		printf("strncmp	5	: %i\n", strncmp(mlem, mlom, 5));
		printf("ft_strequ	: %d\n", ft_strequ(mlem,mlom));
		printf("ft_strnequ 5	: %d\n", ft_strnequ(mlem,mlom, 5));
	}
	printf("\n");
	return (0);
}
