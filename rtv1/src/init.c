/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:13:23 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/03 21:25:53 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_data(t_data *data, t_scene *scene)
{
	data->img = (t_img *)ft_calloc(sizeof(t_img), 1);
	if (data->img == NULL)
		exit_error("img init failed");
	scene->camera.x = 0.0f;
	scene->camera.y = 0.0f;
	scene->camera.z = 2.0f;
	scene->screen_min.x = 0;
	scene->screen_min.y = 0;
	scene->screen_min.z = 0;
	scene->screen_max.x = WINDOW_WIDTH;
	scene->screen_max.y = WINDOW_HEIGHT;
	scene->screen_max.z = 0;
	scene->sphere.x = 0.0f;
	scene->sphere.y = 0.0f;
	scene->sphere.z = 0.0f;
	scene->radius = 0.5f;
}
