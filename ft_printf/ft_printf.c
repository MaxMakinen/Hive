/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:07:26 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/08 19:56:53 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

typedef int *(*funcptr)();			//generic function pointer.
typedef funcptr (*ptrfuncptr)();	//ptr to func returning generic function pointer.

#include <stdio.h>

int main(void)
{
	int x = 1988;

	printf("hex :	%d\n",x);
	printf("itoa :	%s\n",ft_itoa_base(x, 10));
	printf("itox :	%s\n",ft_itoa_base(x, 16));
	printf("itoo :	%s\n",ft_itoa_base(x, 8));
	printf("itob :	%s\n\n",ft_itoa_base(x, 2));
	x = -1988;
	printf("itoa :	%s\n",ft_itoa_base(x, 10));
	printf("itox :	%s\n",ft_itoa_base(x, 16));
	printf("itoo :	%s\n",ft_itoa_base(x, 8));
	printf("itob :	%s\n",ft_itoa_base(x, 2));
}

