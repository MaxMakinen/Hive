/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:13:23 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/26 14:23:57 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
/*
void	init_object(t_object *object)
{
	object->sphere_pos.x = -15.0f;
	object->sphere_pos.y = 5.0f;
	object->sphere_pos.z = -45.0f;
	object->cylinder_pos.x = -30.0f;
	object->cylinder_pos.y = 0.0f;
	object->cylinder_pos.z = -40.0f;
	object->plane_orig.x = 0.0f;
	object->plane_orig.y = -10.0f;
	object->plane_orig.z = 0.0f;
	object->cone_pos.x = 6.0f;
	object->cone_pos.y = 10.0f;
	object->cone_pos.z = -30.0f;
	object->plane_normal.x = 0.0f;
	object->plane_normal.y = 1.0f;
	object->plane_normal.z = 0.0f;
	object->cylinder_normal.x = 0.0f;
	object->cylinder_normal.y = 1.0f;
	object->cylinder_normal.z = 0.0f;
	object->cone_normal.x = 0.0f;
	object->cone_normal.y = 1.0f;
	object->cone_normal.z = 0.0f;
	object->radius = 5.0f;
	object->cylinder_radius = 3.0f;
	object->cone_radius = 2.0f;
	object->cone_height = 5.0f;
	object->radius2 = object->radius * object->radius;
	object->cylinder_radius2 = object->cylinder_radius * object->cylinder_radius;
	object->cone_radius2 = object->cone_radius * object->cone_radius;
	object->sphere.color = 0xff00ff;
	object->plane.color = 0x00ffff;
	object->cylinder.color = 0xffff00;
	object->cone.color = 0x00ff00;
	object->type = 1;
}
*/
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

int init_camera(t_scene *scene)
{
	t_obj	*temp;
	t_vec3f	unit_dir;

	temp = scene->obj;
	while (temp)
	{
		if (temp->type == e_camera)
			break;
		if (temp->next == NULL)
			return (FALSE);
		temp = temp->next;
	}
	if (temp->up.x == 0.0 && temp->up.y == 0.0 && temp->up.z == 0.0)
		temp->up = (t_vec3f){0.0, 1.0, 0.0};
	unit_dir = unit_vec(temp->dir);
	scene->cam = temp;
	scene->horizontal = unit_vec(cross_product(temp->up, temp->dir));
	scene->vertical = unit_vec(cross_product(temp->dir, temp->up));
	scene->horizontal = vec_mult(scene->horizontal, scene->view_width);
	scene->vertical = vec_mult(scene->vertical, scene->view_height);
	//lower_left_corner = origin - horizontal/2 - vertical/2 - w;
	scene->top_left = vec_minus(vec_minus(vec_minus(temp->pos, vec_mult(scene->horizontal, 0.5)), \
	vec_mult(scene->vertical, 0.5)), temp->dir);
	return (TRUE);
}

double	degrees_to_rad(double degrees)
{
	return (degrees * M_PI / 180.0);
}

void	init_data(t_data *data, t_scene *scene)
{
	t_obj	*camera;
	double vert_temp;

	data->img = (t_img *)ft_calloc(sizeof(t_img), 1);
	if (data->img == NULL)
		exit_error("img init failed");
	data->aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	data->fov = 39.6f; //40 degrees works. Current number allegedly copied from blender.
	data->scale = tan(((data->fov * 0.5f) * (M_PI / 180)));
/*
            double vfov, // vertical field-of-view in degrees
            double aspect_ratio
        ) {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;
			*/
	vert_temp = degrees_to_rad(40);
	vert_temp = tan(vert_temp/2);
	scene->view_height = 2 * vert_temp;
	scene->view_width = data->aspect_ratio * scene->view_height;
	data->screen_min.x = 0;
	data->screen_min.y = 0;
	data->screen_min.z = 0;
	data->screen_max.x = WINDOW_WIDTH;
	data->screen_max.y = WINDOW_HEIGHT;
	data->screen_max.z = 0;
//	init_object(&scene->object);
	if (!(init_camera(scene)))
		exit_error("camera init failed");
	init_map(&data->map);
}
