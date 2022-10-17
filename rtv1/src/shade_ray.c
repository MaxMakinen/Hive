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

static t_vec3f	get_light(t_hit *new_hit, t_ray *ray, t_hit *hit, t_obj *light)
{
	t_vec3f	color;

	color = vec_mult(light->col, light->brightness);
	color = vec_mult(color, ALBEDO);
	color = vec_div(color, 4 * M_PI * hit->dist);
	color = vec_mult(color, \
	ft_clamp(dot_product(hit->normal, ray->dir), 0.0, 1.0));
	return (color);
}

static t_vec3f	get_spec(t_hit *new_hit, t_ray *ray, t_hit *hit, t_obj *light)
{
	t_vec3f	color;
	t_vec3f	reflected;
	t_vec3f	specular;

	reflected = reflect_ray(vec_invert(ray->dir), hit->normal);
	color = light->col;
	specular = vec_mult(vec_mult(color, light->brightness), \
	pow(ft_clamp(dot_product(reflected, vec_invert(hit->ray->dir)), 0.0, 1.0), \
	hit->obj->n));
	return (specular);
}

static int	final_color(t_vec3f *col, t_vec3f *spec, t_hit *hit)
{
	t_rgb	color;
	t_vec3f	temp;
	t_vec3f	surface;

	if (hit->obj->shiny == 1)
		*col = vec_plus(vec_mult(*col, hit->obj->kd), \
		vec_mult(*spec, hit->obj->ks));
	temp = vec_times(*col, get_pattern(hit));
	temp = gamma_correct(temp);
	temp.x = ft_clamp(temp.x, 0, 1);
	temp.y = ft_clamp(temp.y, 0, 1);
	temp.z = ft_clamp(temp.z, 0, 1);
	color.rgb[0] = (unsigned char)ft_lerp(temp.x, 0, 255);
	color.rgb[1] = (unsigned char)ft_lerp(temp.y, 0, 255);
	color.rgb[2] = (unsigned char)ft_lerp(temp.z, 0, 255);
	return (color.color);
}

int	shade_ray(t_scene *scene, t_hit *hit, t_obj *light)
{
	t_hit	new_hit;
	t_ray	ray;
	t_vec3f	col;
	t_vec3f	spec;

	col = (t_vec3f){0, 0, 0};
	spec = (t_vec3f){0, 0, 0};
	while (light)
	{
		while (light != NULL && light->type != e_light)
			light = light->next;
		if (light != NULL)
		{
			prep_ray_light(&ray, hit, light);
			cast_ray(&ray, scene, &new_hit);
			if (new_hit.dist > hit->dist)
			{
				col = vec_plus(col, get_light(&new_hit, &ray, hit, light));
				if (hit->obj->shiny == 1)
					spec = vec_plus(spec, get_spec(&new_hit, &ray, hit, light));
			}
			light = light->next;
		}
	}
	return (final_color(&col, &spec, hit));
}
