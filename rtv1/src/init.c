/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:13:23 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/08 10:59:46 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_object(t_object *object)
{
	object->sphere_pos.x = 5.0f;
	object->sphere_pos.y = 4.0f;
	object->sphere_pos.z = 0.0f;
	object->cylinder_pos.x = 0.0f;
	object->cylinder_pos.y = 0.0f;
	object->cylinder_pos.z = 0.0f;
	object->plane_orig.x = 0.0f;
	object->plane_orig.y = 0.0f;
	object->plane_orig.z = 0.0f;
	object->plane_normal.x = 0.0f;
	object->plane_normal.y = 1.0f;
	object->plane_normal.z = 0.0f;
	object->radius = 5.0f;
	object->cylinder_radius = 3.0f;
	object->radius2 = object->radius * object->radius;
	object->cylinder_radius2 = object->cylinder_radius * object->cylinder_radius;
	object->sphere.color = 0xffff00ff;
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
	data->aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	data->fov = 39.6f; //40 degrees works. Current number allegedly copied from blender.
	data->scale = tan(((data->fov * 0.5f) * (M_PI / 180)));
	data->screen_min.x = 0;
	data->screen_min.y = 0;
	data->screen_min.z = 0;
	data->screen_max.x = WINDOW_WIDTH;
	data->screen_max.y = WINDOW_HEIGHT;
	data->screen_max.z = 0;
	init_object(&scene->object);
	init_map(&data->map);
}
