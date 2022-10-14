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

static void	prep_ray_light(t_ray *ray, t_hit *hit, t_obj *light)
{
	ray->orig = hit->pos;
	ray->dir = vec_minus(light->pos, hit->pos);
	hit->dist = vec_len(ray->dir);
	ray->dir = normalize(ray->dir);
}

t_rgb	color_mult(t_rgb color, double num)
{
	color.rgb[0] *= num;
	color.rgb[1] *= num;
	color.rgb[2] *= num;
	return (color);
}

static t_vec3f	get_light(t_hit *new_hit, t_ray *ray, t_hit *hit, t_obj *light)
{
	t_vec3f	color;

	color = (t_vec3f){light->color.rgb[0], \
	light->color.rgb[1], light->color.rgb[2]};
	new_hit->pos = get_intersect(ray->orig, ray->dir, new_hit->dist);
	color = vec_mult(color, ALBEDO * light->brightness);
	color = vec_div(color, 4 * M_PI * hit->dist);
	color = vec_mult(color, \
	ft_clamp(dot_product(hit->normal, ray->dir), 0.0, 1.0));
	color.x = ft_clamp(color.x, 0, 255);
	color.y = ft_clamp(color.y, 0, 255);
	color.z = ft_clamp(color.z, 0, 255);
	return (color);
}

static int	final_color(t_vec3f *col, int hits, t_hit *hit)
{
	t_rgb	color;

	*col = vec_div(*col, hits);
	*col = gamma_correct(*col);
	color.rgb[0] = (unsigned char)ft_clamp(col->x * \
	hit->obj->color.rgb[0], 0, 255);
	color.rgb[1] = (unsigned char)ft_clamp(col->y * \
	hit->obj->color.rgb[1], 0, 255);
	color.rgb[2] = (unsigned char)ft_clamp(col->z * \
	hit->obj->color.rgb[2], 0, 255);
	return (color.color);
}

int	shade_ray(t_scene *scene, t_hit *hit, t_obj *light)
{
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
			prep_ray_light(&ray, hit, light);
			cast_ray(&ray, scene, &new_hit);
			if (new_hit.dist > hit->dist)
				col = vec_plus(col, get_light(&new_hit, &ray, hit, light));
			hits++;
			light = light->next;
		}
	}
	return (final_color(&col, hits, hit));
}
