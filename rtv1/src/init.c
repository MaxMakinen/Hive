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

double	degrees_to_rad(double degrees)
{
	return (degrees * M_PI / 180.0);
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

int init_camera(t_scene *scene, double aspect_ratio)
{
	t_obj	*temp;
	t_vec3f	unit_dir;
	double vert_temp;

	temp = scene->obj;
	while (temp)
	{
		if (temp->type == e_camera)
			break;
		if (temp->next == NULL)
			return (FALSE);
		temp = temp->next;
	}
	scene->cam = temp;
	if (temp->up.x == 0.0 && temp->up.y == 0.0 && temp->up.z == 0.0)
		temp->up = (t_vec3f){0.0, 1.0, 0.0};
	/*
    public:
        camera(
            point3 lookfrom,
            point3 lookat,
            vec3   vup,
            double vfov, // vertical field-of-view in degrees
            double aspect_ratio
        ) {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            auto w = unit_vector(lookfrom - lookat);
            auto u = unit_vector(cross(vup, w));
            auto v = cross(w, u);

            origin = lookfrom;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - w;
	*/
	vert_temp = degrees_to_rad(scene->cam->vfov / 2.0);
	vert_temp = tan(vert_temp);
	scene->view_height = vert_temp;
	scene->view_width = aspect_ratio * scene->view_height;

	t_vec3f w, u, v, origin, horiz2, vert2;
	origin = temp->pos;
	w = normalize(vec_minus(temp->pos, temp->dir));
	if (vec_compare(w, temp->up))
		w.z += 0.0000001;
	u = normalize(cross_product(temp->up, w));
	v = cross_product(w, u);

	scene->horizontal = (vec_mult(u, scene->view_width));
	scene->vertical = (vec_mult(v, scene->view_height));

	horiz2 = vec_mult(scene->horizontal, 0.5);
	vert2 = vec_mult(scene->vertical, 0.5);

	scene->lower_left = (vec_minus(vec_minus(vec_minus(temp->pos, vec_mult(scene->horizontal, 0.5)), \
	vec_mult(scene->vertical, 0.5)), w));
	
	return (TRUE);
}


void	init_data(t_data *data, t_scene *scene)
{
	t_obj	*camera;
	double vert_temp;

	data->img = (t_img *)ft_calloc(sizeof(t_img), 1);
	if (data->img == NULL)
		exit_error("img init failed");
	data->aspect_ratio = (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT;
	data->fov = 39.6f; //40 degrees works. Current number allegedly copied from blender.
	data->scale = tan(((data->fov * 0.5f) * (M_PI / 180)));
	data->screen_min.x = 0;
	data->screen_min.y = 0;
	data->screen_min.z = 0;
	data->screen_max.x = WINDOW_WIDTH;
	data->screen_max.y = WINDOW_HEIGHT;
	data->screen_max.z = 0;
	data->flag = 0;
//	init_object(&scene->object);
	if (!(init_camera(scene, data->aspect_ratio)))
		exit_error("camera init failed");
	init_map(&data->map);
}
