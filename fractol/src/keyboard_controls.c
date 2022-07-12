/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:08:57 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/12 14:37:10 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == KEY_ESC)
		clean_exit(data);
	if (keysym == ARROW_LEFT)
		data->offset.x -= 0.1f;
	if (keysym == ARROW_RIGHT)
		data->offset.x += 0.1f;
	if (keysym == ARROW_UP)
		data->offset.y -= 0.1f;
	if (keysym == ARROW_DOWN)
		data->offset.y += 0.1f;
	if (keysym == NUM_PLUS)
		zoom(data, data->zoom.x);
	if (keysym == NUM_MINUS)
		zoom(data, data->zoom.y);
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
	return (0);
}
