/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:16:23 by dpalacio          #+#    #+#             */
/*   Updated: 2022/04/28 16:27:16 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Zooms view in and out scrolling the mouse wheel up and down
int	mouse_wheel(int key, int x, int y, t_data *data)
{
	if (key == 4)
	{
		data->zoom += 1;
		data->x_off -= data->map_width / 2;
		data->y_off -= data->map_height / 2;
	}
	if (key == 5)
	{
		if (data->zoom > 1)
		{
			data->zoom -= 1;
			if (data->zoom == 1 && data->view == 1)
				data->zoom = 2;
			else
			{
				data->x_off += data->map_width / 2;
				data->y_off += data->map_height / 2;
			}
		}
	}
	draw(data);
	return (1);
}

//Changes the color scheme with the mouse right click
int	right_click(int key, int x, int y, t_data *data)
{
	x = 0;
	y = 0;
	if (key == 2)
	{
		data->color_scheme++;
		if (data->color_scheme == 4)
			data->color_scheme = 0;
		while (y < data->map_height)
		{
			while (x < data->map_width)
			{
				choose_color(data, x, y);
				x++;
			}
			x = 0;
			y++;
		}
		draw(data);
	}
	return (1);
}
