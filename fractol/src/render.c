/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:53:35 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/13 09:39:33 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	reset_values(t_data *data)
{
	data->screen_min.x = 0;
	data->screen_min.y = 0;
	data->screen_max.x = WINDOW_WIDTH;
	data->screen_max.y = WINDOW_HEIGHT;
	data->world_min.x = -2.0;
	data->world_min.y = -1.0;
	data->world_max.x = 1.0;
	data->world_max.y = 1.0;
}

int	render(t_data *data)
{
	reset_values(data);
	screen_to_world(data, data->screen_min, &data->world_min);
	screen_to_world(data, data->screen_max, &data->world_max);
//	mandelbrot(data);
	julia(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
			data->img->mlx_img, 0, 0);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 10, 0, "Max iterations:");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 110, 10, 0, ft_itoa(data->max_iterations));
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 30, 0, "Scale:");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 50, 30, 0, ft_itoa(data->scale.x));
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 50, 0, "Zoom:");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 50, 50, 0, ft_itoa(data->zoom.x * 100));
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 70, 0, "Offset X:");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 80, 70, 0, ft_itoa(data->offset.x * 100));
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 90, 0, "Offset Y:");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 80, 90, 0, ft_itoa(data->offset.y * 100));
	/*
	int	x;
	int	y;

	y = 0;
	if (data->win_ptr == NULL)
		return (1);
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			img_pix_put(data->img, x, y, mandel(x ,y));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
			data->img->mlx_img, 0, 0);
	*/
	return (0);
}

void	mandelbrot(t_data *data)
{
	double	x_scale;
	double	y_scale;
	double	x_pos;
	double	y_pos;
	int		x;
	int		y;
	int		iteration;

	x_scale = (data->world_max.x - data->world_min.x) / (float)(data->screen_max.x) - (float)(data->screen_min.x);
	y_scale = (data->world_max.y - data->world_min.y) / (float)(data->screen_max.y) - (float)(data->screen_min.y);

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
