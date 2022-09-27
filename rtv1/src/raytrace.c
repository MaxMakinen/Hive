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


t_vec3f	get_intersect(t_vec3f origin, t_vec3f direction, double distance)
{
	t_vec3f	intersect;

	intersect.x = origin.x + direction.x * distance;
	intersect.y = origin.y + direction.y * distance;
	intersect.z = origin.z + direction.z * distance;
	return (intersect);
}

int	quadratic_formula(double a, double b, double c, double *t0, double *t1)
{
	double	discriminant;
	double	temp;

	discriminant = b * b - 4.0f * a * c;
	if (discriminant > 0.0f)
	{
		if (b > 0)
			temp = -0.5 * (b + sqrtf(discriminant));
		else
			temp = -0.5 * (b - sqrtf(discriminant));
		*t1 = temp / a;
		*t0 = c / temp;
		return (TRUE);
	}
	else if (discriminant == 0)
	{
		*t0 = -0.5f * b / a;
		*t1 = *t0;
		return (TRUE);
	}
	return (FALSE);
}

t_vec3f	get_direction(t_data *data, double x, double y)
{
	t_vec3f	direction;

	direction.x = (((2.0f * ((x + 0.5f) / (double)data->screen_max.x)) - 1.0f) * data->aspect_ratio) * data->scale;
	direction.y = (1.0f - (2.0f * ((y + 0.5f) / (double)data->screen_max.y))) * data->scale;
	direction.z = -1.0f;
	direction = normalize(direction);
	return (direction);
}

t_vec3f	get_direction2(t_data *data, double x, double y, t_scene *scene)
{
	t_vec3f	direction;

	x /= (data->screen_max.x - 1.0);
	y /= (data->screen_max.y - 1.0);
	direction = vec_minus(vec_plus(vec_plus(scene->lower_left, vec_mult(scene->horizontal, x)), \
	vec_mult(scene->vertical, y)), scene->cam->pos);
	return (direction);
}

int	check_intersect(t_scene *scene, t_obj *obj, t_ray *ray, double *temp, double *t1)
{

	if (obj->type == e_sphere)
	{
		if(!(sphere_intersect(scene, ray, obj, temp, t1)))
			return (FALSE);
	}
	else if (obj->type == e_plane)
	{
		if(!(plane_intersect(scene, ray, obj, temp, t1)))
			return (FALSE);
	}
	else if (obj->type == e_cylinder)
	{
		if(!(cylinder_intersect(scene, ray, obj, temp, t1)))
			return (FALSE);
	}
	else if (obj->type == e_cone)
	{
		if(!(cone_intersect(scene, ray, obj, temp, t1)))
			return (FALSE);
	}
	return (TRUE);
}
/*
t_obj	*find_lights(t_scene *scene, t_obj *light)
{
	t_obj	*temp;

	temp = scene->obj;

}*/
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

	new_ray.orig = hit->pos;
	light = scene->obj;
	shadow.color = 0;
	hits = 0;
	col = (t_vec3f){color->rgb[0], color->rgb[1], color->rgb[2]};
	while (light != NULL && light)
	{
		while (light != NULL && light->type != e_light)
			light = light->next;
		if (light != NULL && light)
		{

			new_ray.dir = vec_minus(light->pos, new_ray.orig);
			light_dist = vec_len(new_ray.dir);
			new_ray.dir = normalize(new_ray.dir);
			object = scene->obj;
			closest = INFINITY;
			while (object != NULL && object)
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
		if (closest <= light_dist)
		{
			color = color;
		//	return (FALSE);
		}
		else
		{
			angle = ft_clamp(dot_product(hit->normal, new_ray.dir), 0.0, 1.0);
			*color = color_mult(hit->obj->color, angle);
			col = vec_plus(col, (t_vec3f){color->rgb[0], color->rgb[1], color->rgb[2]});
			hits++;
		}
		if (light && light->next != NULL)
			light = light->next;
		else
		 break;
	}
	if (hits > 0)
	{
		color->rgb[0] = col.x / hits;
		color->rgb[1] = col.y / hits;
		color->rgb[2] = col.z / hits;
		return (TRUE);
	}
	return (FALSE);
}


void	render_scene(t_scene *scene, t_data *data)
{
	int			x;
	int			y;
	t_vec3f		intersection;
	//t_vec3f		color;
	double		closest;
	double		t0;
	double		t1;
	t_obj		*camera;
	t_obj		*light;
	t_obj		*object;
	t_obj		*closest_obj;
	t_hit		hit;
	t_ray		ray;
	t_rgb		color;
	
	camera = scene->obj;
	while (camera->type != e_camera)
		camera = camera->next;
	light = scene->obj;
	//MAKE LIGHT LINKED LISTT IN STRUCT
	object = scene->obj;
	closest = 0.0f;
	y = data->screen_min.y;
	while (y < data->screen_max.y)
	{
		x = data->screen_min.x;
		while (x < data->screen_max.x)
		{
			ft_bzero(&hit, sizeof(t_hit));
			ft_bzero(&ray, sizeof(t_ray));
			closest = 0.0f;
			ray.dir = get_direction2(data, (double)x, (double)y, scene);
			ray.orig = camera->pos;
			while (object != NULL && object)
			{
				if (object->type > e_light)
				{
					if (check_intersect(scene, object, &ray, &t0, &t1))
					{
						if (t0 < closest || closest == 0.0f || t0 == 0.0f)
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
			light = scene->obj;
			y = data->screen_max.y - y - 1;
			object = scene->obj;
//			intersection = get_intersect(camera->pos, direction, closest);
			hit.pos = get_intersect(camera->pos, ray.dir, closest);
			hit.obj = closest_obj;
			get_normal(closest_obj, &hit);
			if (closest > 0.0f)
			{
			/*	if (shade_ray(scene, &ray, &hit, &color))
					data->map.ptr[y][x] = color.color;
				else
					data->map.ptr[y][x] = 0;
			*/	norm_dot_color(data, &light->pos, x, y, &hit);
			}
			else
				data->map.ptr[y][x] = 0x222222;
			x++;
		}
		y++;
	}
	
}
