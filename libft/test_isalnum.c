/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isalnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:26:45 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/18 13:37:43 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <ctype.h>

int	main(int argc, char **argv)
{
	char a = 'd';
	char b = 9;
	char c = '5';
	char d = 27;

	printf("a : %d\n", ft_isalnum(a));
	printf("a : %d\n", isalnum(a));
	printf("b : %d\n", ft_isalnum(b));
	printf("b : %d\n", isalnum(b));
	printf("c : %d\n", ft_isalnum(c));
	printf("c : %d\n", isalnum(c));
	printf("d : %d\n", ft_isalnum(d));
	printf("d : %d\n", isalnum(d));
	return (0);
}
