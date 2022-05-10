/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:07:26 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/09 12:40:15 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
void	ft_itoa_base_fd(int num, int base, int fd);

int main(void)
{
	int x = 1988;

	printf("hex :	%d\n",x);
	printf("itoa :	%s\n",ft_itoa_base(x, 10));
	printf("itox :	%s\n",ft_itoa_base(x, 16));
	printf("itoo :	%s\n",ft_itoa_base(x, 8));
	printf("itob :	%s\n\n",ft_itoa_base(x, 2));
	printf("itoa_fd\n");
	ft_itoa_base_fd(x, 10, 1);
	printf("\n");
	x = -1988;
	printf("itoa :	%s\n",ft_itoa_base(x, 10));
	printf("itox :	%s\n",ft_itoa_base(x, 16));
	printf("itoo :	%s\n",ft_itoa_base(x, 8));
	printf("itob :	%s\n",ft_itoa_base(x, 2));
	printf("itoa_fd\n");
	ft_itoa_base_fd(x, 10, 1);
	printf("\n");

}

