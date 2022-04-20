/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:06:27 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/20 13:31:02 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"
	
int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl("Usage: fdf <input file>");
		return(1);
	}
	data.map = input(argv[1], &data.map);

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

	int y = 0;
	int x;
	while (y < data.map.y_max)
	{
		x = 0;
		while (x < data.map.x_max)
		{
			data.map.coords[y][x].vect.x -= data.map.x_max / 2;
			data.map.coords[y][x].vect.y -= data.map.y_max / 2;
			x++;
		}
		y++;
	}
//	printf("vect x : %i\nvect y : %i\nvect z : %i\n",data.map.coords[1][1].vect.x, data.map.coords[1][1].vect.y, data.map.coords[1][1].vect.z);
//	data.map.coords[1][1].vect = *matrix_to_vec(mat_mul(rotate_x(1), vec_to_matrix(&data.map.coords[1][1].vect)));
//	printf("vect x : %i\nvect y : %i\nvect z : %i\n",data.map.coords[1][1].vect.x, data.map.coords[1][1].vect.y, data.map.coords[1][1].vect.z);

	/* setup hooks */
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	//CHANGE INTO MLX_KEY_HOOK OR WHATEVER
	mlx_key_hook(data.win_ptr, &handle_keypress, &data);
//	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
//	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
