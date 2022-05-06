/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:13:23 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/06 13:56:10 by mmakinen         ###   ########.fr       */
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
		ft_error("MLX ERROR init");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, \
			WINDOW_HEIGHT, name);
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		ft_error("MLX ERROR img");
	}
	data->img->mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, \
			WINDOW_HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->mlx_img, \
			&data->img->bpp, &data->img->line_len, &data->img->endian);
}

void	prep_camera(t_map *map)
{
	map->camera.x = 1.0f;
	map->camera.y = 1.0f;
	map->camera.z = 1.0f;
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
	map->f_fov = 90.0f;
	map->f_near = 1.1f;
	map->f_far = 1000.0f;
	map->rot_x = prep_matrix(4, 4);
	map->rot_y = prep_matrix(4, 4);
	map->rot_z = prep_matrix(4, 4);
	map->proj = prep_projection_matrix(map, prep_matrix(4, 4));
	prep_camera(map);
}

void	center_coords(t_data *data)
{
	data->map->offset.x = (data->map->x_max / 2) * -1;
	data->map->offset.y = (data->map->y_max / 2) * -1;
	data->map->offset.z = 1.0f;
}
