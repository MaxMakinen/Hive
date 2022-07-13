/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:06:25 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/13 11:24:10 by mmakinen         ###   ########.fr       */
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

	if (data->julia_stop == 0)
		screen_to_world(data, data->mouse.pos, &data->julia);
	x_scale = (data->world_max.x - data->world_min.x) / (float)(data->screen_max.x) - (float)(data->screen_min.x);
	y_scale = (data->world_max.y - data->world_min.y) / (float)(data->screen_max.y) - (float)(data->screen_min.y);

	
	x_pos = data->world_min.x;
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
			real = x_pos;
			imag = y_pos;
			iteration = 0;
			while ((real * real + imag * imag) < 4.0 && iteration < data->max_iterations)
			{
				temp_x = real * real - imag * imag + data->julia.x;
				imag = 2 * real *imag + data->julia.y;
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
