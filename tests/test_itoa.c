/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoatest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:42:56 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/05 16:08:11 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int main (void)
{
	char *str;
	int i = 0;

	ft_putstr("test 1 :");
	ft_putstr(ft_itoa(1988));
	ft_putstr("\ntest 2 :");
	str = ft_itoa(1988);
	ft_putstr(str);
	ft_putstr("\ntest 2 :");
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (0);
}
