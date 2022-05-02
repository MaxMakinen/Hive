/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:08:57 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/02 17:25:45 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void numpad(t_data *data, int keysym)
{
	if(keysym == NUM7)
		roll(data, -0.1);
	if(keysym == NUM9)
		roll(data, 0.1f);
	if(keysym == NUM6)
		yaw(data, -0.1f);
	if(keysym == NUM4)
		yaw(data, 0.1f);
	if(keysym == NUM8)
		pitch(data, -0.1f);
	if(keysym == NUM2)
		pitch(data, 0.1f);
	if(keysym == NUM1)
		rot_bottomleft(data);
	if(keysym == NUM3)
		rot_bottomright(data);
	if(keysym == NUM5 || keysym == 9)
		spin(data);
	if(keysym == NUM0)
		rot_flag(data);
	if(keysym == NUM_PLUS)
		zoom(data, 10);
	if(keysym == NUM_MINUS)
		zoom(data, -10);
}

void	view_control(t_data *data, int keysym)
{
	if(keysym == KEY_2)
		set_ortho(data);
	if(keysym == KEY_3)
		set_persp(data);
	if(keysym == KEY_1)
		reset_view(data);
}

int handle_keypress(int keysym, t_data *data)
{
	if (keysym >= 65429 && keysym <= 65453)
		numpad(data, keysym);
	if (keysym >= 49 && keysym <= 52)
		view_control(data, keysym);
	if (keysym == KEY_ESC)
		clean_exit(data);
	if(keysym == KEY_Q)
		roll(data, -0.1f);
	if(keysym == KEY_E)
		roll(data, 0.1f);
	if(keysym == KEY_W)
		pitch(data, -0.1f);
	if(keysym == KEY_S)
		pitch(data, 0.1f);
	if(keysym == KEY_D)
		yaw(data, -0.1f);
	if(keysym == KEY_A)
		yaw(data, 0.1f);
	if(keysym == KEY_PLUS)
		zoom(data, -1);
	if(keysym == KEY_MINUS)
		zoom(data, 1);
	project(data->map, data->map->proj);
	render(data);
	printf("Keypress: %d\n", keysym);
	return (0);
}
