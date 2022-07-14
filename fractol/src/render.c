/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:53:35 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/14 09:13:06 by mmakinen         ###   ########.fr       */
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
	data->fractal[data->function](data);
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
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 110, 0, "Multi:");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 50, 110, 0, ft_itoa(data->multi));
	return (0);
}
