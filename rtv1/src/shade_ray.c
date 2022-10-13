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

static void	prep_ray_light(t_ray *ray, t_hit *hit, t_obj *light, \
double *light_dist)
{
	ray->orig = hit->pos;
	ray->dir = vec_minus(light->pos, hit->pos);
	*light_dist = vec_len(ray->dir);
	ray->dir = normalize(ray->dir);
}

t_rgb	color_mult(t_rgb color, double num)
{
	color.rgb[0] *= num;
	color.rgb[1] *= num;
	color.rgb[2] *= num;
	return (color);
}

static t_vec3f	get_color(t_hit *new_hit, t_ray *ray, t_hit *hit, t_obj *light)
{
	t_rgb	color;

	new_hit->pos = get_intersect(ray->orig, ray->dir, new_hit->dist);
	color = color_mult(hit->obj->color, \
	ft_clamp(dot_product(hit->normal, ray->dir), 0.0, 1.0));
	return ((t_vec3f){color.rgb[0], color.rgb[1], color.rgb[2]});
}

static unsigned int	final_color(t_vec3f *col, int hits)
{
	t_rgb	color;

	color.rgb[0] = (unsigned char)((unsigned int)(col->x / hits) % 255);
	color.rgb[1] = (unsigned char)((unsigned int)(col->y / hits) % 255);
	color.rgb[2] = (unsigned char)((unsigned int)(col->z / hits) % 255);
	return ((unsigned int)color.color);
}

unsigned int	shade_ray(t_scene *scene, t_hit *hit, t_obj *light)
{
	double	light_dist;
	int		hits;
	t_hit	new_hit;
	t_ray	ray;
	t_vec3f	col;

	hits = 0;
	col = (t_vec3f){0, 0, 0};
	while (light)
	{
		while (light != NULL && light->type != e_light)
			light = light->next;
		if (light != NULL)
		{
			prep_ray_light(&ray, hit, light, &light_dist);
			cast_ray(&ray, scene, &new_hit);
			if (new_hit.dist > light_dist)
				col = vec_plus(col, get_color(&new_hit, &ray, hit, light));
			hits++;
			light = light->next;
		}
	}
	return (final_color(&col, hits));
}
