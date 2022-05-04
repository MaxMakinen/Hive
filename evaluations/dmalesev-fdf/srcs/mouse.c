/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:53:34 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 14:47:16 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	slider(t_utils *utils, int min, int max, int *slider)
{
	*slider += utils->move_x;
	if (*slider > max)
		*slider = max;
	if (*slider < min)
		*slider = min;
	init_proj(utils);
	init_pmatrix(utils);
}

void	left_button(t_utils *u, int x, int y)
{
	if (x > u->screen_x / 5 && x < u->img.max_x)
	{
		u->map_x += u->move_x;
		u->map_y += u->move_y;
	}
	else if (x >= 80 && x <= 349 && y >= 150 && y <= 176)
		slider(u, 0, 255, &u->slid.red);
	else if (x >= 80 && x <= 349 && y >= 200 && y <= 226)
		slider(u, 0, 255, &u->slid.green);
	else if (x >= 80 && x <= 349 && y >= 250 && y <= 276)
		slider(u, 0, 255, &u->slid.blue);
	else if (x >= 80 && x <= 294 && y >= 300 && y <= 326)
		slider(u, -100, 100, &u->slid.elev);
}

int	mouse_move(int x, int y, void *param)
{
	t_utils	*u;

	u = param;
	u->move_x = x - u->mouse_x;
	u->move_y = y - u->mouse_y;
	if ((u->state & 1) == 1)
		left_button(u, x, y);
	if ((u->state & 2) == 2 && x > u->screen_x / 5 && x < u->img.max_x)
	{
		u->rot.beta -= u->move_x;
		u->rot.alpha += u->move_y;
		rot_overflows(u);
	}
	u->map_color = combine_channels(u->slid.red, u->slid.green, u->slid.blue);
	u->mouse_x = x;
	u->mouse_y = y;
	return (0);
}

int	mouse_up(int button, int x, int y, void *param)
{
	t_utils	*utils;

	utils = param;
	button = int_to_bit(button);
	utils->state -= button;
	utils->mouse_x = x;
	utils->mouse_y = y;
	return (0);
}

int	mouse_down(int button, int x, int y, void *param)
{
	t_utils	*utils;

	utils = param;
	button = int_to_bit(button);
	if ((button & 16) == 16 && utils->scale <= 15000)
		utils->scale *= 1.5;
	if ((button & 8) == 8 && utils->scale > 10)
		utils->scale /= 1.5;
	render_screen(utils);
	utils->state += button;
	utils->mouse_x = x;
	utils->mouse_y = y;
	return (0);
}
