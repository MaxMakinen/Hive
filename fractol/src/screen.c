/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:25:13 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/25 14:27:40 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	screen_to_world(t_data *data, t_screen screen, t_coord *world)
{
	world->x = (double)(screen.x) / data->scale + data->offset.x;
	world->y = (double)(screen.y) / data->scale + data->offset.y;
}

void	zoom(t_data *data, double zoom)
{
	data->scale *= zoom;
	if (data->scale < 1.0)
		data->scale = 1.0;
}
