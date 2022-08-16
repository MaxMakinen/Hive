/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multibrot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:02:37 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/26 16:34:11 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	assign(t_coord *to, t_coord from)
{
	to->x = from.x;
	to->y = from.y;
}

static int	get_iteration(t_data *data, t_coord pos, t_coord imag_num)
{
	int		iteration;
	double	powe;
	double	ata;
	double	temp_x;

	iteration = 0;
	while ((imag_num.x * imag_num.x + imag_num.y * imag_num.y) < 4.0 \
			&& iteration < data->max_iterations)
	{
		powe = pow((imag_num.x * imag_num.x + \
					imag_num.y * imag_num.y), (data->multi / 2.0));
		ata = data->multi * atan2(imag_num.y, imag_num.x);
		if (data->mandel == 0)
			assign(&pos, data->julia);
		temp_x = powe * cos(ata) + pos.x;
		imag_num.y = powe * sin(ata) + pos.y;
		imag_num.x = temp_x;
		iteration++;
	}
	return (iteration);
}

void	set_scale(t_data *data, t_coord *scale)
{
	scale->x = (data->world_max.x - data->world_min.x) / \
			(double)(data->screen_max.x) - (double)(data->screen_min.x);
	scale->y = (data->world_max.y - data->world_min.y) / \
			(double)(data->screen_max.y) - (double)(data->screen_min.y);
}

void	multibrot(t_data *data)
{
	t_coord		scale;
	t_coord		pos;
	t_screen	screen;
	t_coord		imag_num;

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
			assign(&imag_num, pos);
			img_pix_put(data->img, screen.x, screen.y, \
					get_color(data, get_iteration(data, pos, imag_num)));
			pos.x += scale.x;
			screen.x++;
		}
		pos.y += scale.y;
		screen.y++;
	}
}
