/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:07:26 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/11 11:55:08 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
void	ft_itoa_base_fd(int num, int base, int fd);

int main(void)
{
	int x = 1988;

/*	printf("hex :	%d\n",x);
	printf("itoa :	%s\n",ft_itoa_base(x, 10));
	printf("itox :	%s\n",ft_itoa_base(x, 16));
	printf("itoo :	%s\n",ft_itoa_base(x, 8));
	printf("itob :	%s\n\n",ft_itoa_base(x, 2));
*/	
	write(1, "itoa_fd : ", 10);
	ft_itoa_base_fd(x, 10, 1);
	write(1, "\n", 1);
	write(1, "itoa_fdx : ", 11);
	ft_itoa_base_fd(x, 16, 1);
	write(1, "\n", 1);
	write(1, "itoa_fdo : ", 11);
	ft_itoa_base_fd(x, 8, 1);
	write(1, "\n", 1);
	write(1, "itoa_fdb : ", 11);
	ft_itoa_base_fd(x, 2, 1);
	write(1, "\n", 1);
	x = -1988;
/*	printf("itoa :	%s\n",ft_itoa_base(x, 10));
	printf("itox :	%s\n",ft_itoa_base(x, 16));
	printf("itoo :	%s\n",ft_itoa_base(x, 8));
	printf("itob :	%s\n",ft_itoa_base(x, 2));
*/
	write(1, "itoa_fd : ", 10);
	ft_itoa_base_fd(x, 10, 1);
	write(1, "\n", 1);
	write(1, "itoa_fdx : ", 11);
	ft_itoa_base_fd(x, 16, 1);
	write(1, "\n", 1);
	write(1, "itoa_fdo : ", 11);
	ft_itoa_base_fd(x, 8, 1);
	write(1, "\n", 1);
	write(1, "itoa_fdb : ", 11);
	ft_itoa_base_fd(x, 2, 1);
	write(1, "\n", 1);
	return (0);
}

