/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:08:57 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/06 14:08:07 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	numpad(t_data *data, int keysym)
{
	if (keysym == NUM7)
		roll(data, -0.01);
	if (keysym == NUM9)
		roll(data, 0.01f);
	if (keysym == NUM6)
		yaw(data, -0.01f);
	if (keysym == NUM4)
		yaw(data, 0.01f);
	if (keysym == NUM8)
		pitch(data, -0.01f);
	if (keysym == NUM2)
		pitch(data, 0.01f);
	if (keysym == NUM1)
		rot_bottomleft(data);
	if (keysym == NUM3)
		rot_bottomright(data);
	if (keysym == NUM5 || keysym == 9)
		spin(data);
	if (keysym == NUM0)
		rot_flag(data);
	if (keysym == NUM_PLUS)
		zoom(data, -100 + data->map->f_fov);
	if (keysym == NUM_MINUS)
		zoom(data, 100 - data->map->f_fov);
}

void	view_control(t_data *data, int keysym)
{
	if (keysym == KEY_1)
		reset_view(data);
	if (keysym == KEY_2)
		set_ortho(data);
	if (keysym == KEY_3)
		set_persp(data);
	if (keysym == KEY_4)
		flatten(data, 1);
	if (keysym == KEY_5)
		flatten(data, (-1));
}

void	wasd(t_data *data, int keysym)
{
	if (keysym == KEY_Q)
		roll(data, -0.1f);
	if (keysym == KEY_E)
		roll(data, 0.1f);
	if (keysym == KEY_W)
		pitch(data, -0.1f);
	if (keysym == KEY_S)
		pitch(data, 0.1f);
	if (keysym == KEY_D)
		yaw(data, -0.1f);
	if (keysym == KEY_A)
		yaw(data, 0.1f);
}

void	pan_camera(t_data *data, int keysym)
{
	if (keysym == ARROW_LEFT)
		data->map->camera.x -= 0.1f;
	if (keysym == ARROW_RIGHT)
		data->map->camera.x += 0.1f;
	if (keysym == ARROW_UP)
		data->map->camera.y -= 0.1f;
	if (keysym == ARROW_DOWN)
		data->map->camera.y += 0.1f;
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym >= NUM_MIN && keysym <= NUM_MAX)
		numpad(data, keysym);
	if (keysym >= KEY_MIN && keysym <= KEY_MAX)
		view_control(data, keysym);
	if (keysym >= LETTER_MIN && keysym <= LETTER_MAX)
		wasd(data, keysym);
	if (keysym >= ARROW_MIN && keysym <= ARROW_MAX)
		pan_camera(data, keysym);
	if (keysym == KEY_ESC)
		clean_exit(data);
	if (keysym == KEY_PLUS)
		zoom(data, -1);
	if (keysym == KEY_MINUS)
		zoom(data, 1);
	project(data->map, data->map->proj);
	render(data);
	return (0);
}
