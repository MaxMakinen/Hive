/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:25:13 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/13 08:59:00 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//world should be floating point and screen should be int.
void	world_to_screen(t_data *data, t_coord world, t_screen *screen)
{
	screen->x = (int)((world.x - data->offset.x) * data->scale.x);
	screen->y = (int)((world.y - data->offset.y) * data->scale.y);
}

void	screen_to_world(t_data *data, t_screen screen, t_coord *world)
{
	world->x = (double)(screen.x) / data->scale.x + data->offset.x;
	world->y = (double)(screen.y) / data->scale.y + data->offset.y;
}

void	zoom(t_data *data, double zoom)
{
	data->scale.x *= zoom;
	data->scale.y *= zoom;
	if (data->scale.x < 1.0 || data->scale.y < 1.0)
	{
		data->scale.x = 1.0;
		data->scale.y = 1.0;
	}
}
