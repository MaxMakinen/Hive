/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:06:25 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/25 13:54:59 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_iteration(t_data *data, t_coord imag_num)
{
	int			iteration;
	double		temp_x;

	iteration = 0;
	while ((imag_num.x * imag_num.x + imag_num.y * imag_num.y) < 4.0 && \
			iteration < data->max_iterations)
	{
		temp_x = imag_num.x * imag_num.x - imag_num.y * imag_num.y + \
				data->julia.x;
		imag_num.y = 2 * imag_num.x * imag_num.y + data->julia.y;
		imag_num.x = temp_x;
		iteration++;
	}
	return (iteration);
}

void	julia(t_data *data)
{
	t_coord		scale;
	t_coord		pos;
	t_screen	screen;

	if (data->julia_stop == 0)
		screen_to_world(data, data->mouse.pos, &data->julia);
	set_scale(data, &scale);
	assign(&pos, data->world_min);
	screen.y = data->screen_min.y;
	while (screen.y < data->screen_max.y)
	{
		pos.x = data->world_min.x;
		screen.x = data->screen_min.x;
		while (screen.x < data->screen_max.x)
		{
			img_pix_put(data->img, screen.x, screen.y, \
					get_color(data, get_iteration(data, pos)));
			pos.x += scale.x;
			screen.x++;
		}
		pos.y += scale.y;
		screen.y++;
	}
}
