/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:53:35 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/25 14:50:21 by mmakinen         ###   ########.fr       */
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

void	screen_text(t_data *data)
{
	char	*temp;

	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 10, 0, "Max iterations:");
	temp = ft_itoa(data->max_iterations);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 110, 10, 0, temp);
	free(temp);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 55, 0, "Scale:");
	temp = ft_itoa(data->scale);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 50, 55, 0, temp);
	free(temp);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 100, 0, "Multi:");
	temp = ft_itoa(data->multi);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 50, 100, 0, temp);
	free(temp);
}

int	render(t_data *data)
{
	reset_values(data);
	screen_to_world(data, data->screen_min, &data->world_min);
	screen_to_world(data, data->screen_max, &data->world_max);
	data->fractal[data->function](data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
			data->img->mlx_img, 0, 0);
	screen_text(data);
	return (0);
}
