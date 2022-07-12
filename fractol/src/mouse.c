/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 21:06:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/12 14:45:35 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int mouse_press(int button, int x, int y, t_data *data)
{
	t_coord pre_zoom_mouse;
	t_coord post_zoom_mouse;

	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		screen_to_world(data, data->mouse.pos, &pre_zoom_mouse);
		if (button == MOUSE_SCROLL_UP)
			zoom(data, data->zoom.x);
		if (button == MOUSE_SCROLL_DOWN)
			zoom(data, data->zoom.y);
		screen_to_world(data, data->mouse.pos, &post_zoom_mouse);
		data->offset.x += (pre_zoom_mouse.x - post_zoom_mouse.x);
		data->offset.y += (pre_zoom_mouse.y - post_zoom_mouse.y);
	}
	if (button == MOUSE_MIDDLE)
	{
		data->mouse.pressed = 1;
		data->mouse.pos.x = x;
		data->mouse.pos.y = y;
	}
	return (1);
}

int	mouse_release(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	(void)button;
	if (data->mouse.pressed == 1)
		data->mouse.pressed = 0;
	return (1);
}

int	mouse_move(int x, int y, t_data *data)
{
	if (data->mouse.pressed == 1)
	{
		data->offset.x -= (x - data->mouse.pos.x) / data->scale.x;
		data->offset.y -= (y - data->mouse.pos.y) / data->scale.y;
	}
	data->mouse.pos.x = x;
	data->mouse.pos.y = y;
	return (1);
}
