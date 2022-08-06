/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:13:23 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/06 23:22:55 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_object(t_object *object)
{
	object->sphere_pos.x = 2.0f;
	object->sphere_pos.y = 1.0f;
	object->sphere_pos.z = -8.0f;
	object->plane_orig.x = 0.0f;
	object->plane_orig.y = 0.0f;
	object->plane_orig.z = 0.0f;
	object->normal.x = 0.0f;
	object->normal.y = 1.0f;
	object->normal.z = 0.0f;
	object->radius = 2.0f;
	object->radius2 = object->radius * object->radius;
	object->color.color = 0xffff00ff;
	object->plane.color = 0xff00ffff;
	object->type = 1;
}

void	init_map(t_map *map)
{
	int	*itemp;
	int	x;

	map->pool = (int *)ft_calloc(WINDOW_WIDTH * WINDOW_HEIGHT, sizeof(int));
	map->ptr = (int **)ft_calloc(WINDOW_HEIGHT, sizeof(int *));
	itemp = map->pool;
	x = 0;
	while (x < WINDOW_HEIGHT)
	{
		map->ptr[x] = itemp;
		itemp += WINDOW_WIDTH;
		x++;
	}
}

void	init_data(t_data *data, t_scene *scene)
{
	data->img = (t_img *)ft_calloc(sizeof(t_img), 1);
	if (data->img == NULL)
		exit_error("img init failed");
	scene->camera.x = 0.0f;
	scene->camera.y = 1.0f;
	scene->camera.z = 3.0f;
	scene->screen_min.x = 0;
	scene->screen_min.y = 0;
	scene->screen_min.z = 0;
	scene->screen_max.x = WINDOW_WIDTH;
	scene->screen_max.y = WINDOW_HEIGHT;
	scene->screen_max.z = 0;
	scene->light.x = -5.0f;
	scene->light.y = 5.0f;
	scene->light.z = 5.0f;
	scene->light_dir.x = 1.0f;
	scene->light_dir.y = -1.0f;
	scene->light_dir.z = 1.0f;
	scene->max_objects = 1;
	init_object(&scene->object);
	init_map(&data->map);
}
