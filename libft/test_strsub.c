/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsubtest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:03:52 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/08 15:21:34 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int main (void)
{
	int start = 6;
	int len = 8;
	char *str = "jungle monkeys eat a more varied diet than those growing in zoo's\n";

	ft_putstr("strlen = ");
	ft_putnbr(ft_strlen(str));
	ft_putchar('\n');
	ft_putstr(str);
	ft_putstr("start = 6, len 8\n-l-");
	ft_putstr(ft_strsub(str,start,len));
	ft_putchar('\n');
	start = 40;
	len = 70;
	ft_putstr("start = 40, len 70\n-l-");
	ft_putstr(ft_strsub(str,start,len));
	ft_putchar('\n');
	start = 68;
	len = 80;
	ft_putstr("start = 68, len 80\n-l-");
	ft_putstr(ft_strsub(str,start,len));
	ft_putchar('\n');
	return (0);
}
