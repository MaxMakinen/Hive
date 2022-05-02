/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:06:27 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/02 11:22:48 by mmakinen         ###   ########.fr       */
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

void init_map(t_map *map)
{
	map->x_max = 0;
	map->y_max = 0;
	map->z_max = 0;
	map->z_min = 0;
	map->anglex = 0.0f;
	map->angley = 0.0f;
	map->anglez = 0.0f;
	map->zoom = 0;
	map->f_pov = 90.0f;
	map->f_near = 1.1f;
	map->f_far = 1000.0f;
	map->rot_x = prep_matrix(4, 4);
	map->rot_y = prep_matrix(4, 4);
	map->rot_z = prep_matrix(4, 4);
	map->proj = prep_projection_matrix(map, prep_matrix(4, 4));
}

// Center map in middle of screen
void center_coords(t_data *data)
{
	int x;
	int y;
	float centx;
	float centy;

	centx = (data->map.x_max / 2) * -1;
	centy = (data->map.y_max / 2) * -1;
	y = 0;
	while (y < data->map.y_max)
	{
		x = 0;
		while (x < data->map.x_max)
		{
			vec_adjust(&data->map.coords[y][x].vect, centx, centy);
			data->map.coords[y][x].vect.z *= -1;
			x++;
		}
		y++;
	}
}
/*
void	prep_hooks(t_data *data)
{

}
*/

int key_win(int button, int x, int y, t_data *data)
{
	int o;

	o = 0;
	o += data->img.endian;
	printf("Mouse in Win2, button %d at %dx%d.\n",button,x,y);
	return (1);
}

int mouse(int x, int y, t_data *data)
{
	int o;

	o = 0;
	o += data->img.endian;
	printf("Mouse moving in Win3, at %dx%d.\n",x,y);
	return (1);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl("Usage: fdf <input file>");
		return(1);
	}
	init_map(&data.map);
	data.map = input(argv[1], &data.map);
	center_coords(&data);

	project(&data.map, data.map.proj);


	/* Create the image */
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return(MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr)	;
		return (MLX_ERROR);
	}

	// setup hooks
	data.bckgrnd.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.bckgrnd.addr = mlx_get_data_addr(data.bckgrnd.mlx_img, &data.bckgrnd.bpp, &data.bckgrnd.line_len, &data.bckgrnd.endian);
	render_background(&data.bckgrnd, 0xFF8080);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.bckgrnd.mlx_img, 0, 0);

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

//	mlx_loop_hook(data.mlx_ptr, &render, &data);

	mlx_hook(data.win_ptr, 6, 1L<<0, &mouse, &data);
	mlx_key_hook(data.win_ptr, key_win, &data);

//	mlx_key_hook(data.win_ptr, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 2, 1L<<0, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 3, 1l<<0, &handle_keyrelease, &data);
	mlx_hook(data.win_ptr, 17, 1l<<0, close, &data);

	render(&data);
	mlx_loop(data.mlx_ptr);
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

	// we will exit the loop if there's no window left, and execute this code
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
//	mlx_destroy_display(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.img.mlx_img);

	
	free(data.mlx_ptr);
	return (0);
}
