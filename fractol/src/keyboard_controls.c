/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:08:57 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/13 08:54:54 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_keypress(int keysym, t_data *data)
{
	t_coord pre_zoom_mouse;
	t_coord post_zoom_mouse;
	if (keysym == KEY_ESC)
		clean_exit(data);
	if (keysym == ARROW_LEFT)
		data->offset.x -= 3.0f / data->scale.x;
	if (keysym == ARROW_RIGHT)
		data->offset.x += 3.0f / data->scale.x;
	if (keysym == ARROW_UP)
		data->offset.y -= 3.0f / data->scale.x;
	if (keysym == ARROW_DOWN)
		data->offset.y += 3.0f / data->scale.x;
	if (keysym == NUM_PLUS || keysym == NUM_MINUS)
	{
		screen_to_world(data, data->mouse.pos, &pre_zoom_mouse);
		if (keysym == NUM_PLUS)
			zoom(data, data->zoom.x);
		if (keysym == NUM_MINUS)
			zoom(data, data->zoom.y);
		screen_to_world(data, data->mouse.pos, &post_zoom_mouse);
		data->offset.x += (pre_zoom_mouse.x - post_zoom_mouse.x);
		data->offset.y += (pre_zoom_mouse.y - post_zoom_mouse.y);
	}
	if (keysym == KEY_Q)
		data->max_iterations += 64;
	if (keysym == KEY_A)
		data->max_iterations -= 64;
	if (keysym == NUM1)
	{
		data->zoom.x += 0.1;
		data->zoom.y -= 0.1;
		if (data->zoom.x < 1.1 || data->zoom.y > 0.9)
		{
			data->zoom.x = 1.1;
			data->zoom.y = 0.9;
		}
	}
	if (keysym == NUM2)
	{
		data->zoom.x -= 0.1;
		data->zoom.y += 0.1;
		if (data->zoom.x < 1.1 || data->zoom.y > 0.9)
		{
			data->zoom.x = 1.1;
			data->zoom.y = 0.9;
		}
	}
	if (keysym == NUM0)
	{
		data->zoom.x = 1.1;
		data->zoom.y = 0.9;
	}
	if (keysym == NUM9)
	{
		data->offset.x = -3,0;
		data->offset.y = -1.5;
	}
	if (keysym == NUM8)
		reset_scale(data);
	return (0);
}
