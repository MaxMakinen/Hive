/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:07:54 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/10 12:08:12 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_rgb col_x_col(t_rgb col1, t_rgb col2){
	t_rgb	new;

	new.rgb[0] = col1.rgb[0] * col2.rgb[0];
	new.rgb[1] = col1.rgb[1] * col2.rgb[1];
	new.rgb[2] = col1.rgb[2] * col2.rgb[2];
	return (new);
}

int	shade_ray(t_scene *scene, t_ray *ray, t_hit *hit, t_rgb *color)
{
	t_rgb	shadow;
	t_obj	*light;
	t_obj	*object;
	t_obj	*closest_obj;
	double	t0;
	double	t1;
	double	light_dist;
	double	closest;
	double	angle;
	double	len;
	int		hits;
	t_hit	new_hit;
	t_ray	new_ray;
	t_vec3f	col;
	int	vis = 0;
	double albedo = 0.18 / M_PI;
	t_rgb light_color;

	new_ray.orig = hit->pos;
	ft_bzero(&new_hit, sizeof(new_hit));
	light = get_obj(scene->obj, e_light);
	shadow.color = 0;
	hits = 0;
	col = (t_vec3f){0, 0, 0};
	while (light != NULL && light)
	{
		while (light != NULL && light->type != e_light)
			light = light->next;
		if (light)
		{
			shadow.color = 0;
			albedo *= light->brightness;
			light_color = color_mult(light->color, albedo);
			new_ray.dir = vec_minus(light->pos, new_ray.orig);
			light_dist = vec_len(new_ray.dir);
			new_ray.dir = normalize(new_ray.dir);
			object = scene->obj;
			closest = INFINITY;
			while (object)
			{
				if (object->type > e_light)
				{
					if (check_intersect(scene, object, &new_ray, &t0, &t1))
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
		}
		new_hit.pos = get_intersect(new_ray.orig, new_ray.dir, closest);
		new_hit.obj = closest_obj;
		shadow = hit->obj->color;
		if (closest <= light_dist)
			shadow.color = 0;
		angle = ft_clamp(dot_product(hit->normal, new_ray.dir), 0.0, 1.0);
		shadow = color_mult(shadow, albedo);
	//	shadow = col_x_col(shadow, light_color);
		shadow = color_mult(shadow, angle);
		col = vec_plus(col, (t_vec3f){shadow.rgb[0], shadow.rgb[1], shadow.rgb[2]});
		hits++;
		if (light && light->next != NULL)
		{
			light = light->next;
		}
		else
			break;
	}
	if (hits > 0)
	{
		color->rgb[0] = (int)(col.x / hits) % 255;
		color->rgb[1] = (int)(col.y / hits) % 255;
		color->rgb[2] = (int)(col.z / hits) % 255;
		return (TRUE);
	}
	return (FALSE);
}
