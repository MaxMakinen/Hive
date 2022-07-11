/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:25:13 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/11 14:50:28 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//world should be floating point and screen should be int.
void	world_to_screen(t_data *data)
{
	data->screen->x = (int)(data->world->x - data->offset->x);
	data->screen->y = (int)(data->world->y - data->offset->y);
}

void	screen_to_world(t_data *data)
{
	data->world->x = (double)(data->screen->x + data->offset->x);
	data->world->y = (double)(data->screen->y + data->offset->y);
}
