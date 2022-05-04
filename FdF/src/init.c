/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:13:23 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/04 13:25:45 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_data(t_data *data)
{
	data->map = (t_map *)ft_calloc(sizeof(t_map), 1);
	data->img = (t_img *)ft_calloc(sizeof(t_img), 1);
	init_map(data->map);
}

void	create_img(t_data *data, char *name)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		err_msg("MLX ERROR init");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, \
			WINDOW_HEIGHT, name);
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		err_msg("MLX ERROR img");
	}
	data->img->mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, \
			WINDOW_HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->mlx_img, \
			&data->img->bpp, &data->img->line_len, &data->img->endian);
}

void	init_map(t_map *map)
{
	map->x_max = 0;
	map->y_max = 0;
	map->z_max = 0;
	map->z_min = 0;
	map->anglex = 0.0f;
	map->angley = 0.0f;
	map->anglez = 0.0f;
	map->zoom = 0;
	map->rotate = 0;
	map->f_pov = 90.0f;
	map->f_near = 1.1f;
	map->f_far = 1000.0f;
	map->rot_x = prep_matrix(4, 4);
	map->rot_y = prep_matrix(4, 4);
	map->rot_z = prep_matrix(4, 4);
	map->proj = prep_projection_matrix(map, prep_matrix(4, 4));
}

// Center map in middle of screen
void	center_coords(t_data *data)
{
	data->map->offset.x = (data->map->x_max / 2) * -1;
	data->map->offset.y = (data->map->y_max / 2) * -1;
	data->map->offset.z = 1.0f;
}
/*
void	setup_hooks(t_data *data)
{
//	mlx_loop_hook(data->mlx_ptr, rotate, data);

	mlx_hook(data->win_ptr, 6, 1L<<8, mouse_move, data);
	mlx_hook(data->win_ptr, 4, 1L<<2, mouse_press, data);

	mlx_hook(data->win_ptr, 2, 1L<<0, handle_keypress, data);
	mlx_hook(data->win_ptr, 17, 0, destroy, data);
}
*/
