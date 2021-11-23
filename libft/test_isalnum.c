/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isalnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:26:45 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/19 11:06:08 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char a = 'd';
	char b = 9;
	char c = '5';
	char d = 27;

	printf("ft_isanlum	: %d\n", ft_isalnum(a));
	printf("isalnum		: %d\n", isalnum(a));
	printf("ft_isalnum	: %d\n", ft_isalnum(b));
	printf("isalnum		: %d\n", isalnum(b));
	printf("ft_isalnum	: %d\n", ft_isalnum(c));
	printf("isalnum		: %d\n", isalnum(c));
	printf("ft_isalnum	: %d\n", ft_isalnum(d));
	printf("isalnum		: %d\n", isalnum(d));
	return (0);
}
