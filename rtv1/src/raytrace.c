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

t_obj *get_obj(t_obj* head, enum e_type type)
{
	while (head && head->next != NULL && head->type != type)
		head = head->next;
	if (head->type != type)
		return(NULL);
	else
		return(head);
}

void	render_scene(t_scene *scene, t_data *data)
{
	int			x;
	int			y;
	t_vec3f		intersection;
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
	
	ft_bzero(&hit, sizeof(hit));
	camera = scene->obj;
	while (camera->type != e_camera)
		camera = camera->next;
	light = scene->obj;
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
			light = get_obj(scene->obj, e_light);
			y = data->screen_max.y - y - 1;
			object = scene->obj;
			hit.pos = get_intersect(camera->pos, ray.dir, closest);
			hit.obj = closest_obj;
			get_normal(closest_obj, &hit, &ray);
			if (closest > 0.0f)
			{
				if (shade_ray(scene, &ray, &hit, &color))
					data->map.ptr[y][x] = color.color;
				else
					data->map.ptr[y][x] = 0;
			//	norm_dot_color(data, &light->pos, x, y, &hit);
			}
			else
				data->map.ptr[y][x] = 0x222222;
			x++;
		}
		y++;
	}
	
}
