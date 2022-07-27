/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:08:57 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/26 17:39:47 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mode(t_data *data, int keysym)
{
	if (keysym == KEY_1)
		data->color = 0;
	if (keysym == KEY_2)
		data->color = 1;
	if (keysym == KEY_3)
		data->color = 2;
	if (keysym == KEY_4)
		data->color = 3;
}

void	pan(t_data *data, int keysym)
{
	if (keysym == ARROW_LEFT)
		data->offset.x -= 3.0f / data->scale;
	if (keysym == ARROW_RIGHT)
		data->offset.x += 3.0f / data->scale;
	if (keysym == ARROW_UP)
		data->offset.y -= 3.0f / data->scale;
	if (keysym == ARROW_DOWN)
		data->offset.y += 3.0f / data->scale;
}

void	adjust_settings(t_data *data, int keysym)
{
	if (keysym == NUM8)
		reset_scale(data);
	if (keysym == NUM4)
		data->multi -= 1.0;
	if (keysym == NUM5)
		data->multi += 1.0;
	if (keysym == NUM6)
		data->mandel = (data->mandel + 1) & 1;
	if (keysym == NUM0)
	{
		if (data->function == 2)
			data->function = 3;
		else if (data->function == 3)
			data->function = 2;
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == KEY_ESC)
		clean_exit(data);
	else if (keysym >= ARROW_MIN && keysym <= ARROW_MAX)
		pan(data, keysym);
	else if (keysym == NUM_PLUS || keysym == NUM_MINUS)
		zoom_and_offset(data, keysym);
	else if (keysym >= NUM_MIN && keysym <= NUM_MAX)
		adjust_settings(data, keysym);
	else if (keysym == KEY_Q)
		data->max_iterations += 64;
	else if (keysym == KEY_A)
		data->max_iterations -= 64;
	else if (keysym >= KEY_MIN && keysym <= KEY_MAX)
		mode(data, keysym);
	return (0);
}
