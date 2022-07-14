/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinsky.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:14:00 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/13 18:54:08 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	sierpinsky(t_data *data)
{
	t_coord	top;
	t_coord left;
	t_coord right;
	int	corner;
	int	iterations;
	double	x_scale;
	double	y_scale;

	iterations = 0;
	x_scale = (data->world_max.x - data->world_min.x) / (float)(data->screen_max.x) - (float)(data->screen_min.x);
	y_scale = (data->world_max.y - data->world_min.y) / (float)(data->screen_max.y) - (float)(data->screen_min.y);

	top.x = (double)WINDOW_WIDTH / 2.0;
	top.y = ((double)WINDOW_HEIGHT * 0.2);
	left.x = top.x - (((double)WINDOW_HEIGHT * 0.6) * sin(1.04719755));
	left.y = ((double)WINDOW_HEIGHT * 0.8);
	right.x = top.x + left.x;
	right.y = left.y;
	if (data->julia_stop == 0 && data->mandel == 0)
	{
		if (data->mandel == 0)
		{
			data->julia.x = ft_lerp(ft_norm(rand(), 0.0, (float)RAND_MAX), 0, (float)WINDOW_WIDTH);
			data->julia.y = ft_lerp(ft_norm(rand(), 0.0, (float)RAND_MAX), 0, (float)WINDOW_HEIGHT);
			data->mandel = 1;
		}
		while (iterations < 10000)
		{
			corner = rand() % 3;
			if (corner == 0)
			{
				data->julia.x += (top.x - data->julia.x) / 2.0;
				data->julia.y += (top.y - data->julia.y) / 2.0;
			}
			if (corner == 1)
			{
				data->julia.x += (right.x - data->julia.x) / 2.0;
				data->julia.y += (right.y - data->julia.y) / 2.0;
			}
			if (corner == 2)
			{
				data->julia.x += (left.x - data->julia.x) / 2.0;
				data->julia.y += (left.y - data->julia.y) / 2.0;
			}
			img_pix_put(data->img, data->julia.x, data->julia.y, 0);
			iterations++;
		}
	}
}
/*
	x_pos = data->world_min.x;
	y_pos = data->world_min.y;
	y = data->screen_min.y;

	double temp_x;
	double f_x;
	double f_y;

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
				f_y = 2 * f_x *f_y + y_pos;
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
*/
