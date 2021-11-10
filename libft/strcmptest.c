/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmptest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:40:52 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/08 16:08:01 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int main (int argc, char **argv)
{
	if (argc < 3 || argc > 3)
	{
		ft_putstr("Give two strings to compare\n");
		return (1);
	}
	ft_putstr("ft_strcmp : ");
	ft_putnbr(ft_strcmp(argv[1], argv[2]));
	ft_putstr("\nstrcmp : ");
	ft_putnbr(ft_strcmp(argv[1], argv[2]));
	ft_putchar('\n');
	ft_putstr("ft_strncmp 5 : ");
	ft_putnbr(ft_strncmp(argv[1], argv[2], 5));
	ft_putstr("\nstrncmp 5 : ");
	ft_putnbr(ft_strncmp(argv[1], argv[2], 5));
	ft_putchar('\n');
	ft_putstr("ft_strequ : ");
	ft_putnbr(ft_strequ(argv[1], argv[2]));
	ft_putstr("\nft_strnequ 5 : ");
	ft_putnbr(ft_strnequ(argv[1], argv[2], 5));
	ft_putchar('\n');
	return (0);
}
