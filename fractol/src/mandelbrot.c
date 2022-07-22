/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:03:30 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/22 17:39:05 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_data *data)
{
	double	x_scale;
	double	y_scale;
	double	x_pos;
	double	y_pos;
	int		x;
	int		y;
	int		iteration;
	double	temp_x;
	double	f_x;
	double	f_y;

	x_scale = (data->world_max.x - data->world_min.x) / (float)(data->screen_max.x) - (float)(data->screen_min.x);
	y_scale = (data->world_max.y - data->world_min.y) / (float)(data->screen_max.y) - (float)(data->screen_min.y);

	x_pos = data->world_min.x;
	y_pos = data->world_min.y;
	y = data->screen_min.y;

	while (y < data->screen_max.y)
	{
		x_pos = data->world_min.x;
		x = data->screen_min.x;
		while (x < data->screen_max.x)
		{
			f_x = 0.0;
			f_y = 0.0;
			iteration = 0;
			while ((f_x * f_x + f_y * f_y) < 4.0 && iteration < data->max_iterations)
			{
				temp_x = f_x * f_x - f_y * f_y + x_pos;
				f_y = 2 * f_x * f_y + y_pos;
				f_x = temp_x;
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
