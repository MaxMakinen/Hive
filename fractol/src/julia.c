/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:06:25 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/13 10:24:05 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia(t_data *data)
{
	double	x_scale;
	double	y_scale;
	double	x_pos;
	double	y_pos;
	int		x;
	int		y;
	int		iteration;

	double	radius;
	t_coord	temp;

	screen_to_world(data, data->mouse.pos, &temp);
	radius = sqrt(temp.x * temp.x + temp.y * temp.y);

	radius = 4.0;
	data->world_min.x = -radius;
	data->world_min.y = -radius;
	data->world_max.x = radius;
	data->world_max.y = radius;
	
	x_scale = (data->world_max.x - data->world_min.x) / (float)(data->screen_max.x) - (float)(data->screen_min.x);
	y_scale = (data->world_max.y - data->world_min.y) / (float)(data->screen_max.y) - (float)(data->screen_min.y);

	/*
	x_pos = data->world_min.x;
	y_pos = data->world_min.y;
	*/
	x_pos = data->screen_min.x;
	y_pos = data->world_min.y;
	y = data->screen_min.y;

	double temp_x;
	double real;
	double imag;

	while (y < data->screen_max.y)
	{
		x_pos = data->world_min.x;
		x = data->screen_min.x;
		while (x < data->screen_max.x)
		{
			real = temp.x;
			imag = temp.y;
			iteration = 0;
			while ((real * real + imag * imag) < (radius * radius) && iteration < data->max_iterations)
			{
				temp_x = real * real - imag * imag + x_pos;
				imag = 2 * real *imag + y_pos;
				real = temp_x;
				iteration++;
			}
			img_pix_put(data->img, x, y, get_color(data, iteration));
			x_pos += x_scale;
			x++;
		}
		y_pos += y_scale;
		y++;
	}
}
