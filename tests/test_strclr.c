/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strclrtest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:53:01 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/10 11:09:20 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("give one string\n");
		return (1);
	}
	ft_putstr(argv[1]);
	ft_putstr(": END\n");
	ft_strclr(argv[1]);
	ft_putstr(argv[1]);
	ft_putstr(": END\n");
	return (0);
}
