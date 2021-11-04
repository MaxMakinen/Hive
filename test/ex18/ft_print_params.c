/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:19:19 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/02 15:08:41 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_params(char *str)
{
	int	check;

	check = 0;
	while (str[check] != '\0')
	{
		ft_putchar(str[check]);
		check++;
	}
	ft_putchar('\n');
}

int	main(int argc, char **argv)
{
	int	counter;

	counter = 1;
	while (counter < argc)
	{
		ft_print_params(argv[counter]);
		counter++;
	}
	return (0);
}
