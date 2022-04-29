/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:06:27 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/29 13:32:37 by mmakinen         ###   ########.fr       */
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

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl("Usage: fdf <input file>");
		return(1);
	}
	data.map = input(argv[1], &data.map);

	// Center map in middle of screen
	
	float centx = data.map.x_max / 2;
	float centy = data.map.y_max / 2;
	centx = -centx;
	centy = -centy;
	int x, y = 0;
	while (y < data.map.y_max)
	{
		x = 0;
		while (x < data.map.x_max)
		{
			vec_adjust(&data.map.coords[y][x].vect, centx, centy);
			data.map.coords[y][x].vect.z *= -1;
			x++;
		}
		y++;
	}


	project(&data.map, data.map.proj);


	data.mlx_ptr = mlx_init();
	/* Create the image */
	if (data.mlx_ptr == NULL)
		return(MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr)	;
		return (MLX_ERROR);
	}

	// setup hooks
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);

//	mlx_key_hook(data.win_ptr, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 2, 1L<<0, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 3, 1l<<0, &handle_keyrelease, &data);
	mlx_hook(data.win_ptr, 17, 1l<<0, close, &data);

	mlx_loop(data.mlx_ptr);

	// we will exit the loop if there's no window left, and execute this code
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
//	mlx_destroy_display(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.img.mlx_img);

	
	free(data.mlx_ptr);
	return (0);
}
