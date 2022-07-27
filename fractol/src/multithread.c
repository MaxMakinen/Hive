/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:02:37 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/27 13:13:21 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	set_scale_and_thread(t_data *data, t_coord *scale, t_screen *temp, \
		t_coord *pos)
{
	temp->x = data->screen_min.x + (data->thread * data->thread_size);
	temp->y = data->thread_size + data->thread * data->thread_size;
	scale->x = (data->world_max.x - data->world_min.x) / \
			(double)(data->screen_max.x) - (double)(data->screen_min.x);
	scale->y = (data->world_max.y - data->world_min.y) / \
			(double)(data->screen_max.y) - (double)(data->screen_min.y);
	assign(pos, data->world_min);
}

void	multibrot_thread(t_data *data)
{
	t_coord		scale;
	t_coord		pos;
	t_screen	screen;
	t_coord		imag_num;
	t_screen	temp;

	if (data->julia_stop == 0)
		screen_to_world(data, data->mouse.pos, &data->julia);
	set_scale_and_thread(data, &scale, &temp, &pos);
	screen.y = data->screen_min.y;
	while (screen.y < data->screen_max.y)
	{
		pos.x = (data->world_min.x + (temp.x * scale.x));
		screen.x = temp.x;
		while (screen.x < temp.y)
		{
			assign(&imag_num, pos);
			data->arr_ptr[screen.y][screen.x] = get_iteration(data, pos, imag_num);
//			img_pix_put(data->img, screen.x, screen.y, \
//					get_color(data, get_iteration(data, pos, imag_num)));
			pos.x += scale.x;
			screen.x++;
		}
		pos.y += scale.y;
		screen.y++;
	}
}

void	multithread(t_data *data)
{
	pthread_t	pthread[MAX_THREADS];

	data->thread_size = data->screen_max.x / MAX_THREADS;
	data->thread = 0;
	while (data->thread < MAX_THREADS)
	{
		pthread_create(&pthread[data->thread], NULL, \
				(void *)multibrot_thread, data);
		data->thread++;
	}
	data->thread = 0;
	while (data->thread < MAX_THREADS)
	{
		pthread_join(pthread[data->thread], NULL);
		data->thread++;
	}
	int x = 0;
	int y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			img_pix_put(data->img, x, y, get_color(data, data->arr_ptr[y][x]));
			x++;
		}
		y++;
	}
}
