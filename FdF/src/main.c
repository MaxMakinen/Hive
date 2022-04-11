/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:35:51 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/11 16:05:51 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
	{
	//	write (1, "Usage: fdf <input file>\n", 24);
	//	return (1);
		map = input("./maps/42.fdf", &map);
	}
	else
		map = input(argv[1], &map);
	int	x = 0;
	int	y = 0;
	ft_putstr("x_max : ");
	ft_putnbr(map.x_max);
	ft_putstr("\ty_max : ");
	ft_putnbr(map.y_max);
	ft_putstr("\n");
	while (y < map.y_max)
	{
		x = 0;
		while (x < map.x_max)
		{
			if (!map.coords[y][x].invisible)
				ft_putnbr(map.coords[y][x].height);
			else
				ft_putstr(" ");
			ft_putstr("	");
			x++;
		}
		ft_putchar('\n');
		y++;
	}
	free(map.coords);
	free(map.pool);
	return (0);
}
