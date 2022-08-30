/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_less_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atenhune <atenhune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:40:22 by atenhune          #+#    #+#             */
/*   Updated: 2022/04/07 15:12:56 by atenhune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	int a = -2147483648;
	int *b = &a;
	int **c = &b;
	
	printf("function call: \"%%d %%d %%d\", 42, 352, 0\n");
	ft_printf("%d %d %d\n", 42, 352, 0);
	printf("function call: \"%%d %%d %%d\", 42, -352, -0\n");
	ft_printf("%d %d %d\n", 42, -352, -0);
	printf("function call: \"%%d %%d %%d\", 42, 2147483647, -2147483648\n");
	ft_printf("%d %d %d\n", 42, 2147483647, a);

	printf("function call: \"%%s %%s %%s\", \"MORO\", \"MITA\", \"KUULUU?\"\n");
	ft_printf("%s %s %s\n", "MORO", "MITA", "KUULUU?");
	printf("function call: \"%%s %%s %%s %%s %%s\", \"1\", \"2\", \"3\", \"4\", \"5\"\n");
	ft_printf("%s %s %s %s %s\n", "1", "2", "3", "4", "5");

	printf("function call: \"%%p %%p %%p\", b, c, b\n");
	ft_printf("%p %p %p\n", b, c, b);
}