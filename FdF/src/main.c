/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:06:27 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/02 17:37:57 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
	

void	log_matrix(t_matrix matrix)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (y < matrix.y_max)
	{
		x = 0;
		while (x < matrix.x_max)
		{
			printf("[%f] ", matrix.m[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
}

void	log_vector(t_vector vec)
{
	printf("[%f]\n[%f]\n[%f]\n", vec.x, vec.y, vec.z);
}


int show(t_data *data)
{
	project(data->map, data->map->proj);
	render(data);
	return (1);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		err_msg("Usage: fdf <input file>");
	init_data(&data);
	data.map = input(argv[1], data.map);
	center_coords(&data);
	create_img(&data, argv[1]);
//	setup_hooks(&data);

	mlx_loop_hook(data.mlx_ptr, &rotate, &data);
	mlx_hook(data.win_ptr, 4, 1L<<2, mouse_press, &data);
	mlx_hook(data.win_ptr, 2, 1L<<0, handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0, destroy, &data);
	mlx_hook(data.win_ptr, 12, 0, show, &data);
	mlx_loop(data.mlx_ptr);

	
	free(data.mlx_ptr);
	return (0);
}
