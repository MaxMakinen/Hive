/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:13:09 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/31 14:40:51 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	render_scene(t_scene *scene, t_data *data)
{
	int			x;
	int			y;
	t_vec3f		intersection;
	double		closest;
	double		t0;
	double		t1;
	t_obj		*object;
	t_obj		*closest_obj;
	t_hit		hit;
	t_ray		ray;
	t_rgb		color;
	
	y = data->screen_min.y;
	ray.orig = scene->cam->pos;
	while (y < data->screen_max.y)
	{
		x = data->screen_min.x;
		while (x < data->screen_max.x)
		{
			ft_bzero(&hit, sizeof(t_hit));
			object = scene->obj;
			closest = INFINITY;
			ray.dir = get_direction(data, (double)x, (double)y, scene);
			while (object)
			{
				if (object->type > e_light)
				{
					if (check_intersect(object, &ray, &t0, &t1))
					{
						if (t0 < closest)
						{
							closest = t0;
							closest_obj = object;
						}
					}
				}
				if (object->next != NULL)
					object = object->next;
				else
					break;
			}
			y = data->screen_max.y - y - 1;
			hit.pos = get_intersect(scene->cam->pos, ray.dir, closest);
			hit.obj = closest_obj;
			get_normal(closest_obj, &hit, &ray);
			if (closest > 0.0f)
			{
				if (shade_ray(scene, &ray, &hit, &color))
					data->map.ptr[y][x] = color.color;
				else
					data->map.ptr[y][x] = 0;
			//	data->map.ptr[y][x] = norm_dot_color(data, &light->pos, &hit);
			}
			else
				data->map.ptr[y][x] = 0x222222;
			x++;
		}
		y++;
	}
}
