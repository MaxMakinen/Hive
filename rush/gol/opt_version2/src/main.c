/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:42 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/23 18:50:40 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gol.h"

void	init_data(t_data *data)
{
	data->row = 0;
	data->col = 0;
}

void	print_map(t_data *data, char **map)
{
	int	row = 0;
	int	col = 0;

	while (row < data->row)
	{
		col = 0;
		while (col < data->col)
		{
			if (map[row][col] & 1)
				printf("X");
			else
				printf(".");
			col++;
		}
		printf("\n");
		row++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	int		len;

	init_data(&data);
	if (ac == 3)
	{
		prep_map(av[1], &data);
		data.iterations = atoi(av[2]);
		len = data.col * data.row;
		while (data.iterations--)
		{
			gameoflife(&data);
			memcpy(data.pool1, data.pool2, len);
			memset(data.pool2, 0, (sizeof(char) * len));
			data.pool2[len] = '\0';
		}
		print_map(&data, data.map1);
		printf("\n");
	}
}
