/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 09:47:35 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/26 14:24:44 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	clean_exit(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->img);
	free(data->map.pool);
	free(data->map.ptr);
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img = NULL;
	data->map.pool = NULL;
	data->map.ptr = NULL;
	free_objects(data->scene);
	data->scene = NULL;
	exit (0);
}

int	destroy(void *param)
{
	clean_exit(param);
	return (1);
}

void	exit_error(char *str)
{
	ft_putendl(str);
	exit(1);
}

void	draw(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			img_pix_put(data->img, x, y, data->map.ptr[y][x]);
			x++;
		}
		y++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	t_scene	scene;

	if (ac != 2)
		exit_error("Usage: ./rtv1 <input file>");
	scene.name = "default";
	data.scene = &scene;
	read_input(&data, av[1]);
	init_data(&data, &scene);
	render_scene(&scene, &data);
	create_img(&data, "scene");
	draw(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, \
			data.img->mlx_img, 0, 0);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0, destroy, &data);
	mlx_hook(data.win_ptr, 12, 0, render, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
