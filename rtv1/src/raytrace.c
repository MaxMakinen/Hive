/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:13:09 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/13 11:21:53 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	prep_round(t_hit *hit, t_obj **object, t_scene *scene)
{
	*object = scene->obj;
	ft_bzero(hit, sizeof(t_hit));
	hit->dist = INFINITY;
}

static int	determine_color(t_scene *scene, t_hit *hit, t_ray *ray)
{
	int	color;

	color = 0;
	if (hit->dist > 0.0f && hit->dist < INFINITY)
	{
		hit->pos = get_intersect(scene->cam->pos, ray->dir, hit->dist);
		get_normal(hit->obj, hit, ray);
		color = shade_ray(scene, hit, scene->obj);
	}
	return (color);
}

void	cast_ray(t_ray *ray, t_scene *scene, t_hit *hit)
{
	t_obj	*object;

	ft_bzero(hit, sizeof(t_hit));
	object = scene->obj;
	hit->dist = INFINITY;
	while (object != NULL)
	{
		if (object->type > e_light)
			check_intersect(object, ray, hit);
		object = object->next;
	}
}

void	render_scene(t_scene *scene, t_data *data)
{
	int			x;
	int			y;
	t_hit		hit;
	t_ray		ray;

	y = data->screen_min.y - 1;
	ray.orig = scene->cam->pos;
	while (++y < data->screen_max.y)
	{
		x = data->screen_min.x - 1;
		while (++x < data->screen_max.x)
		{
			ray.dir = get_direction(data, (double)x, (double)y, scene);
			cast_ray(&ray, scene, &hit);
			data->map.ptr[data->screen_max.y - y - 1][x] = \
			determine_color(scene, &hit, &ray);
		}
	}
}
