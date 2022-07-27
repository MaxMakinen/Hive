/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:13:23 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/27 13:12:31 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zero_coord(t_coord *coord)
{
	coord->x = 0.0;
	coord->y = 0.0;
}

void	zero_screen(t_screen *screen)
{
	screen->x = 0;
	screen->y = 0;
}

void	reset_scale(t_data *data)
{
	data->scale = (double)WINDOW_HEIGHT / 3.00;
	data->offset.x = -3.0;
	data->offset.y = -1.5;
}

void	set_function_pointers(t_data *data)
{
	data->fractal[0] = &mandelbrot;
	data->fractal[1] = &julia;
	data->fractal[2] = &multibrot;
	data->fractal[3] = &multithread;
}

void	make_array(t_data *data)
{
	int			x;
	double		*temp;
	
	data->arr_pool = (double *)ft_calloc(WINDOW_WIDTH * WINDOW_HEIGHT, sizeof(double));
	data->arr_ptr = (double **)ft_calloc(WINDOW_HEIGHT, sizeof(double *));
	if (!data->arr_pool || !data->arr_ptr)
		exit_error("double array malloc error");
	temp = data->arr_pool;
	x = 0;
	while (x < WINDOW_HEIGHT)
	{
		*(data->arr_ptr + x) = temp;
		temp += WINDOW_WIDTH;
		x++;
	}
}

void	init_data(t_data *data)
{
	data->img = (t_img *)ft_calloc(sizeof(t_img), 1);
	if (data->img == NULL)
		exit_error("img init failed");
	zero_coord(&data->world_min);
	zero_coord(&data->world_max);
	zero_screen(&data->screen_min);
	zero_screen(&data->screen_max);
	zero_coord(&data->offset);
	zero_coord(&data->julia);
	reset_scale(data);
	data->julia_stop = 0;
	data->mandel = 0;
	data->color = 0;
	data->zoom.x = 1.1;
	data->zoom.y = 0.9;
	data->max_iterations = 128;
	data->multi = 2.0;
	set_function_pointers(data);
	data->function = -1;
	data->thread = 0;
	data->cores = (int)sysconf(_SC_NPROCESSORS_ONLN);
	make_array(data);
}
