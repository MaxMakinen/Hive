/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmaptest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:42:20 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/08 17:07:53 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("Give one string");
		return (1);
	}
//	ft_putstr("ft_strmap & ft_toupper : ");
//	ft_putstr(ft_strmap(argv[1],ft_toupper));
//	ft_putchar('\0');
	ft_putstr("ft_striter & ft_toupper : ");
	ft_striter(argv[1],ft_toupper);
	ft_putstr(argv[1]);
	ft_putchar('\0');
	return (0);
}

