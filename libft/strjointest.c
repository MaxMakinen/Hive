/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjointest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:41:09 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/08 14:50:19 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int main (int argc, char **argv)
{
	if (argc < 3 || argc > 3)
	{
		ft_putstr("Need two strings\n");
		return (1);
	}
	ft_putstr(ft_strjoin(argv[1], argv[2]));
	ft_putchar('\0');
	return (0);
}
