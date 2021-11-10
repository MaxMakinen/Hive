/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrimtest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:24:25 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/08 12:49:52 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int main (void)
{
	char *str = "	 	\tbananaman loves peanutbutter sandwiches \n 	";
	char *str2;

	ft_putstr(str);
	ft_putchar('\n');
	str2 = ft_strtrim(str);
	ft_putstr(str2);
	return (0);
}
