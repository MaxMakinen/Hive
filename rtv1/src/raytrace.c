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


t_vec3f	get_intersect(t_vec3f origin, t_vec3f direction, float distance)
{
	t_vec3f	intersect;

	intersect.x = origin.x + direction.x * distance;
	intersect.y = origin.y + direction.y * distance;
	intersect.z = origin.z + direction.z * distance;
	return (intersect);
}

int	quadratic_formula(float a, float b, float c, float *t0, float *t1)
{
	float	discriminant;
	float	temp;

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

//Sphere hit calculation
//(bx^2 + by^2 + bz^2)t2 + (2(axbx + ayby + azbz))t + (ax^2 + ay^2 + az^2 - r^2) = 0
//			A							B							C
//a = ray origin
//b = ray direction
//r = radius
//t = hit distance
//
//Quadratic formula:
//-B+/-sqrt(B^2 - 4 AC) / 2A
	//a = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
	//b = 2.0f * (origin.x * direction.x + origin.y * direction.y + origin.z * direction.z);
	//c = origin.x * origin.x + origin.y * origin.y + origin.z * origin.z - object->radius2;

int	plane_intersect(t_scene *scene, t_vec3f origin, t_vec3f direction, t_vec3f normal, float *intersect, float *t1)
{
	float	denominator;

	*t1 = 0.0f;
	denominator = dot_product(normal, direction);
	if (fabs(denominator) > 0.000001f)
	{
		*intersect = dot_product(origin, normal) / denominator;
		if (*intersect >= 0)
			return (TRUE);
	}
	return (FALSE);
}

int	cone_intersect_OLD(t_scene *scene, t_vec3f origin, t_vec3f direction, t_obj *object, float *t0, float *t1)
{
	float		a;
	float		b;
	float		c;
	double		dir;
	double		orig;
	t_vec3f		normal;

	normal = normalize(object->dir);
	dir = dot_product(direction, normal);
	orig = dot_product(origin, normal);
	float	height = object->height;
	float	constant = object->radius2 / (height * height);
	float	dir2 = dir * dir;
	float	orig2 = orig * orig;
	float	dir_orig = dir * orig;

	a = dot_product(direction, direction) - (constant * dir2) - dir2;
	b = 2.0f * (dot_product(direction, origin) - (constant * dir_orig) - dir_orig);
	c = dot_product(origin, origin) - constant * orig2 - orig2;
	
	if (!quadratic_formula(a, b, c, t0, t1))
		return (FALSE);
	if (*t0 > *t1)
	{
		ft_swapf(t0, t1);
		if (*t0 < 0.0f)
		{
			*t0 = *t1;
			if (*t0 < 0.0f)
				return(FALSE);
		}
	}
	return (TRUE);
}

int	cylinder_intersect_OLD(t_scene *scene, t_vec3f origin, t_vec3f direction, t_obj *object, float *t0, float *t1)
{
	float		a;
	float		b;
	float		c;
	double		dir;
	double		orig;
	t_vec3f		normal;

	normal = normalize(object->dir);
	dir = dot_product(direction, normal);
	orig = dot_product(origin, normal);
	a = dot_product(direction, direction) - (dir * dir);
	b = 2.0f * ((dot_product(direction, origin) - (dot_product(direction, normal) * orig)));
	c = dot_product(origin, origin) - (orig * orig) - object->radius2;
	
	if (!quadratic_formula(a, b, c, t0, t1))
		return (FALSE);
	if (*t0 > *t1)
	{
		ft_swapf(t0, t1);
		if (*t0 < 0.0f)
		{
			*t0 = *t1;
			if (*t0 < 0.0f)
				return(FALSE);
		}
	}
	return (TRUE);
/*
	discriminant = b * b - 4.0f * a * c;
	if (discriminant >= 0.0f)
	{
		t0 = (-b - sqrt(discriminant)) / (2.0f * a);
		if (discriminant > 0.0f)
			t1 = (-b + sqrt(discriminant)) / (2.0f * a);
		if (t0 > t1)
			t0 = t1;
		if (t0 < 0.0f)
		{
			t0 = t1;
			if (t0 < 0.0f)
				return(FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
*/
}

/*MAKE FUNCTION FOR QUADRTIC FORMULA! many intersect formulas use it*/
int	sphere_intersect_OLD(t_scene *scene, t_vec3f origin, t_vec3f direction, float radius2, float *t0, float *t1)
{
	float		a;
	float		b;
	float		c;

	a = dot_product(direction, direction);
	b = 2.0f * dot_product(origin, direction);
	c = dot_product(origin, origin) - radius2;
	
	if (!quadratic_formula(a, b, c, t0, t1))
		return (FALSE);
	if (*t0 > *t1)
	{
		ft_swapf(t0, t1);
		if (*t0 < 0.0f)
		{
			*t0 = *t1;
			if (*t0 < 0.0f)
				return(FALSE);
		}
	}
	return (TRUE);
}

t_vec3f	get_direction(t_data *data, float x, float y)
{
	t_vec3f	direction;

	direction.x = (((2.0f * ((x + 0.5f) / (float)data->screen_max.x)) - 1.0f) * data->aspect_ratio) * data->scale;
	direction.y = (1.0f - (2.0f * ((y + 0.5f) / (float)data->screen_max.y))) * data->scale;
	direction.z = -1.0f;
	direction = normalize(direction);
	return (direction);
}

t_vec3f	get_direction2(t_data *data, float x, float y, t_scene *scene)
{
	t_vec3f	direction;

	x /= (data->screen_max.x - 1.0);
	y /= (data->screen_max.y - 1.0);
	direction = vec_minus(vec_plus(vec_plus(scene->lower_left, vec_mult(scene->horizontal, x)), \
	vec_mult(scene->vertical, y)), scene->cam->pos);
	return (direction);
}

int	check_intersect(t_scene *scene, t_obj *obj, t_obj *camera, t_vec3f *direction, float *temp, float *t1)
{

	if (obj->type == e_sphere)
	{
		if(!(sphere_intersect(scene, vec_minus(camera->pos, obj->pos), *direction, obj->radius2, temp, t1)))
			return (FALSE);
	}
	else if (obj->type == e_plane)
	{
		if(!(plane_intersect(scene, vec_minus(obj->pos, camera->pos), *direction, obj->dir, temp, t1)))
			return (FALSE);
	}
	else if (obj->type == e_cylinder)
	{
		if(!(cylinder_intersect(scene, vec_minus(camera->pos, obj->pos), *direction, obj, temp, t1)))
			return (FALSE);
	}
	else if (obj->type == e_cone)
	{
		if(!(cone_intersect(scene, vec_minus(camera->pos, obj->pos), *direction, obj, temp, t1)))
			return (FALSE);
	}
	return (TRUE);
}

t_vec3f	get_normal(t_obj *object, t_vec3f *intersection)
{
	t_vec3f	normal;
	t_vec3f	forward;

	if (object->type == e_plane)
	{
		normal = normalize(object->dir);
		*intersection = vec_plus(*intersection, vec_mult(normal, BIAS));
	}
	else if (object->type == e_sphere)
	{
		normal = vec_minus(*intersection, object->pos);
		normal = normalize(normal);
		*intersection = vec_plus(*intersection, vec_mult(normal, BIAS));
	}
	else if (object->type == e_cylinder)
	{
		normal = normalize(vec_minus(*intersection, object->pos));
		forward = cross_product(normal, object->dir);
		normal = cross_product(object->dir, forward);
	//	normal = vec_mult(normal, -1.0);
		//normal.y = 0.0f;
		*intersection = vec_plus(*intersection, vec_mult(normal, BIAS));
	}
	else if (object->type == e_cone)
	{
		double tempy;

		normal = vec_minus(*intersection, object->pos);
		//normal.y = 0.0f;
		normal = normalize(normal);
		tempy = normal.y * object->radius / object->height;
		normal = vec_mult(normal, object->height / object->radius);
		normal.y = tempy;
		*intersection = vec_plus(*intersection, vec_mult(normal, BIAS));
	}
	return (normal);
}


void	render_scene(t_scene *scene, t_data *data)
{
	int			x;
	int			y;
	t_vec3f		direction;
	t_vec3f		intersection;
	t_vec3f		color;
	float		closest;
	float		t0;
	float		t1;
	t_obj		*camera;
	t_obj		*light;
	t_obj		*object;
	t_obj		*closest_obj;
	
	camera = scene->obj;
	while (camera->type != e_camera)
		camera = camera->next;
	light = scene->obj;
	//MAKE LIGHT LINKED LISTT IN STRUCT
	while (light->type != e_light)
		light = light->next;
	object = scene->obj;
	closest = 0.0f;
	y = data->screen_min.y;
	while (y < data->screen_max.y)
	{
		x = data->screen_min.x;
		while (x < data->screen_max.x)
		{
			closest = 0.0f;
			color = (t_vec3f){0.0, 0.0, 0.0};
//			direction = get_direction(data, (float)x, (float)y);
			direction = get_direction2(data, (float)x, (float)y, scene);
			while (object != NULL && object)
			{
				if (object->type > e_light)
				{
					if (check_intersect(scene, object, camera, &direction, &t0, &t1))
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
			y = data->screen_max.y - y - 1;
			object = scene->obj;
			intersection = get_intersect(camera->pos, direction, closest);
			if (closest > 0.0f)
			{
				direction = vec_minus(light->pos, intersection);
				direction = normalize(direction);
				norm_dot_color(data, &light->pos, intersection, x, y, closest_obj->color, get_normal(closest_obj, &intersection));
			}
			else
				data->map.ptr[y][x] = 0x222222;
			x++;
		}
		y++;
	}
	
}
/*
void	make_image(t_scene *scene, t_data *data)
{
	int			x;
	int			y;
	t_vec3f		direction;
	t_vec3f		intersection;
	t_vec3f		normal;
	t_vec3f		hitpoint;
	float		temp;
	float		closest;
	float		closest_shadow;
	int 		type;
	t_rgb		*color;

	int	tp = 0;
	temp = 0.0f;
	y = data->screen_min.y;
	while (y < data->screen_max.y)
	{
		x = data->screen_min.x;
		while (x < data->screen_max.x)
		{
			closest = 0.0f;
			closest_shadow = 0.0f;
			direction = get_direction(data, (float)x, (float)y);
			if (plane_intersect(scene, vec_minus(scene->object.plane_orig, scene->camera.pos), direction, scene->object.plane_normal, &temp))
			{
				if (temp < closest || closest == 0.0f)
				{
					closest = temp;
					type = 1;
				}
			}
			if (sphere_intersect(scene, vec_minus(scene->camera.pos, scene->obj->pos), direction, scene->obj->radius2, &temp))
			{
				if (temp < closest || closest == 0.0f)
				{
					closest = temp;
					type = 2;
				}
			}
			if (cylinder_intersect(scene, vec_minus(scene->camera.pos, scene->object.cylinder_pos), direction, &scene->object, &temp))
			{
				if (temp < closest || closest == 0.0f)
				{
					closest = temp;
					type = 3;
				}
			}
			if (cone_intersect(scene, vec_minus(scene->camera.pos, scene->object.cone_pos), direction, &scene->object, &temp))
			{
				if (temp < closest || closest == 0.0f)
				{
					closest = temp;
					type = 4;
				}
			}
			intersection = get_intersect(scene->camera.pos, direction, closest);
			if (type == 1)
			{
				color = &scene->object.plane;
				normal = scene->object.plane_normal;
				normal = normalize(normal);
				intersection = vec_plus(intersection, vec_mult(normal, BIAS));
			}
			else if (type == 2)
			{
				color = &scene->obj->color;
				normal = vec_minus(intersection, scene->obj->pos);
				normal = normalize(normal);
				intersection = vec_plus(intersection, vec_mult(normal, BIAS));
			}
			else if (type == 3)
			{
				color = &scene->object.cylinder;
				normal = vec_minus(intersection, scene->object.cylinder_pos);
				normal = normalize(normal);
				normal.y = 0.0f;
				intersection = vec_plus(intersection, vec_mult(normal, BIAS));
			}
			else if (type == 4)
			{
				color = &scene->object.cone;
				normal = vec_minus(intersection, scene->object.cone_pos);
				normal.y = 0.0f;
				normal = normalize(normal);
				normal = vec_mult(normal, scene->object.cone_height / scene->object.cone_radius);
				normal.y = scene->object.cone_radius / scene->object.cone_height;
				intersection = vec_plus(intersection, vec_mult(normal, BIAS));
			}
			int	shadow;
			if (closest > 0.0f)
			{
				shadow = 0;
//					intersection = vec_plus(scene->camera.pos, direction, closest));
				direction = vec_minus(scene->light->pos, intersection);
				direction = normalize(direction);
				if (tp == 3)
				{
					printf("shadow intersect = %f\nintersection.x = %f\nintersection.y = %f\nintersection.z = %f\n", closest, intersection.x, intersection.y, intersection.z);
						tp = 4;
				}
				if (type)
				{
					if (plane_intersect(scene, vec_minus(scene->object.plane_orig, intersection), direction, scene->object.plane_normal, &temp))
					{
						shadow = 1;
						data->map.ptr[y][x] = 0;	
					}
				}
				if (type)
				{
					if (sphere_intersect(scene, vec_minus(intersection, scene->obj->pos), direction, scene->obj->radius2, &temp))
					{
						if (tp == 4 && temp < 2)
						{
							printf("shadow intersect = %f\nintersection.x = %f\nintersection.y = %f\nintersection.z = %f\n", temp, intersection.x, intersection.y, intersection.z);
							tp = 12;
						}
						shadow = 0;
						data->map.ptr[y][x] = 0;
					}
				}
				if (!shadow)
					norm_dot_color(data, scene, intersection, x, y, *color, normal);
//						angle_color(data, scene, intersection, x, y, *color, normal);
			}
			else
				data->map.ptr[y][x] = 0x222222;
			x++;
		}
		y++;
	}
}
*/
				/*
				length = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
				direction.x = temp.x/length;
				direction.y = temp.y/length;
				direction.z = -1.0f/lenght;
				map[y][x] = ray_trace(scene, scene->camera.pos, direction);
				*/
