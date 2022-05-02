/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:42:07 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/02 15:48:21 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void zoom(t_data *data, int range)
{
	data->map->zoom += range;
}

void rot_flag(t_data *data)
{
	if (data->map->rotate == 1)
		data->map->rotate = 0;
	else
		data->map->rotate = 1;
}

void set_ortho(t_data *data)
{
	data->map->f_pov = 0.0f;
	data->map->zoom =(data->map->x_max + data->map->y_max + data->map->z_max) / 2 * 100;
	if (data->map->zoom < 0)
		data->map->zoom = 0;
	if (data->map->f_pov <= 0)
		data->map->f_pov = 1.0f;
	data->map->proj = prep_projection_matrix(data->map, data->map->proj);
}

void set_persp(t_data *data)
{
	data->map->f_pov = 90.0f;
	data->map->zoom = (data->map->x_max + data->map->y_max + data->map->z_max) / 2;
	if ((int)data->map->f_pov % 10 != 0)
		data->map->f_pov = 10.0f;
	data->map->proj = prep_projection_matrix(data->map, data->map->proj);
}

void reset_view(t_data *data)
{
	data->map->anglex = 0.0f;
	data->map->angley = 0.0f;
	data->map->anglez = 0.0f;
}
