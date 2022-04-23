/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:06:27 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/23 11:46:05 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
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
/*	
	float winx = WINDOW_WIDTH / 2;
	float winy = WINDOW_HEIGHT / 2;
	float centx = data.map.x_max / 2;
	float centy = data.map.y_max / 2;
	float diff;
	diff = (float)ft_abs(data.map.x_max - data.map.y_max);
	centx = -centx;
	centy = -centy;
	int x, y = 0;
*/
	data.map.angle = 0.01f;
	data.proj = prep_projection_matrix();
	
	t_matrix *proj = prep_projection_matrix();
	t_matrix *rotz = prep_rotate_z(0.1f);
	log_matrix(*proj);
	printf("\n[2][2] x : %f	y : %f	z : %f\n", data.map.coords[2][2].vect.x, data.map.coords[2][2].vect.y, data.map.coords[2][2].vect.z);
	printf("[2][0] x : %f	y : %f	z : %f\n", data.map.coords[2][0].vect.x, data.map.coords[2][0].vect.y, data.map.coords[2][0].vect.z);
	project(&data.map, proj);
	printf("\n[2][2] x : %f	y : %f	z : %f\n", data.map.coords[2][2].vect.x, data.map.coords[2][2].vect.y, data.map.coords[2][2].vect.z);
	printf("[2][0] x : %f	y : %f	z : %f\n", data.map.coords[2][0].vect.x, data.map.coords[2][0].vect.y, data.map.coords[2][0].vect.z);


	/*
	t_matrix minmax;
	minmax = *isometric(&data.map, &data.img, 20);	
	printf("0,1 : %f,%f\n", minmax.m[0][0], minmax.m[0][1]);
	printf("2,3 : %f,%f\n", minmax.m[1][0], minmax.m[1][1]);
	centx = ((-minmax.m[0][0]) + minmax.m[0][1]) / 2;
	centy = ((-minmax.m[1][0]) + minmax.m[1][1]) / 2;
	centx = ((minmax.m[0][0]) + minmax.m[0][1]);
	centy = ((minmax.m[1][0]) + minmax.m[1][1]);
	if (minmax.m[0][1] < minmax.m[1][1])
		diff = minmax.m[1][1] - minmax.m[0][1];
	else
		diff = minmax.m[0][1] - minmax.m[1][1];
	centy -= ((diff * 0.75f));
	centx -= (diff);
	printf("cenxt : %f	centy : %f\n", centx, centy);
	centx = -centx;
	centy = -centy;
	printf("cenxt : %f	centy : %f\n", centx, centy);
	while (y < data.map.y_max)
	{
		x = 0;
		while (x < data.map.x_max)
		{
			vec_adjust(&data.map.coords[y][x].vect, centx, centy);
			vec_adjust(&data.map.coords[y][x].vect, winx, winy);
			x++;
		}
		y++;
	}
//	printf("[2][2] x : %f	y : %f	z : %f\n", data.map.coords[2][2].vect.x, data.map.coords[2][2].vect.y, data.map.coords[2][2].vect.z);
//	printf("[2][0] x : %f	y : %f	z : %f\n", data.map.coords[2][0].vect.x, data.map.coords[2][0].vect.y, data.map.coords[2][0].vect.z);
*/
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

/*
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
*/


//	printf("vect x : %i\nvect y : %i\nvect z : %i\n",data.map.coords[1][1].vect.x, data.map.coords[1][1].vect.y, data.map.coords[1][1].vect.z);
//	data.map.coords[1][1].vect = *matrix_to_vec(mat_mul(rotate_x(1), vec_to_matrix(&data.map.coords[1][1].vect)));
//	printf("vect x : %i\nvect y : %i\nvect z : %i\n",data.map.coords[1][1].vect.x, data.map.coords[1][1].vect.y, data.map.coords[1][1].vect.z);

	// setup hooks
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);

	mlx_key_hook(data.win_ptr, &handle_keypress, &data);
//	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
//	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);

	mlx_loop(data.mlx_ptr);

	// we will exit the loop if there's no window left, and execute this code
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);

	
	free(data.mlx_ptr);
	return (0);
}
