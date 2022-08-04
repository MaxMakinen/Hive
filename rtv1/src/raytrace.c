/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:13:09 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/04 23:24:50 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


double	vec_len(t_3vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_3vec	normalize(t_3vec vec)
{
	double	magnitude;

	magnitude = vec_len(vec);
	vec.x = vec.x / magnitude;
	vec.y = vec.y / magnitude;
	vec.z = vec.z / magnitude;
	return (vec);
}

double	dot_product(t_3vec vec1, t_3vec vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

float	get_angle(t_3vec vec1, t_3vec vec2)
{
	return (acos((dot_product(vec1, vec2))/(vec_len(vec1) * vec_len(vec2))));
}

t_3vec	vec_minus(t_3vec vec1, t_3vec vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	vec1.z -= vec2.z;
	return (vec1);
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
float	sphere_intersect(t_scene *scene, t_3vec *direction, t_object *object)
{
	float		a;
	float		b;
	float		c;
	float		t0;
	float		t1;
	float		discriminant;
	t_3vec		origin;

	origin = vec_minus(scene->camera, object->position);
	a = direction->x * direction->x + direction->y * direction->y + direction->z * direction->z;
	b = 2.0f * (origin.x * direction->x + origin.y * direction->y + origin.z * direction->z);
	c = origin.x * origin.x + origin.y * origin.y + \
			origin.z * origin.z - object->radius2;
	discriminant = b * b - 4.0f * a * c;
	if (discriminant >= 0.0f)
	{
		t0 = (-b - sqrt(discriminant)) / (2.0f * a);
		if (discriminant > 0.0f)
			t1 = (-b + sqrt(discriminant)) / (2.0f * a);
		if (t0 > 0.0f)
		{
			t0 = t1;
			if (t0 > 0.0f)
				return(FALSE);
		}
		return (t0);
	}
	return (FALSE);
}

float	plane_intersect(t_scene *scene, t_3vec *direction, t_object *object)
{
	float	denominator;
	t_3vec	origin;
	float	intersect;

	denominator = dot_product(object->normal, *direction);
	if (denominator > 1e-6)
	{
		origin = vec_minus(object->origin, scene->camera);
		intersect = dot_product(origin, object->normal) / denominator;
		if (intersect >= 0)
			return (intersect);
	}
	return (FALSE);
}

void	make_image(t_scene *scene, t_data *data)
{
	int			x;
	int			y;
	float		length;
	t_3vec		direction;
	t_3vec		intersection;
	t_3vec		normal;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_map		map;
	int			*itemp;
	float		t0;
	float		t1;
	t_3vec		origin;
	t_rgb		color;
	float		temp;
	float		aspect_ratio;
	double		angle;

	aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	int	q = 0;
	y = scene->screen_min.y;
	origin = vec_minus(scene->camera, scene->object.position);
	while (y < scene->screen_max.y)
	{
		x = scene->screen_min.x;
			while (x < scene->screen_max.x)
			{
				direction.x = (((float)x / (float)scene->screen_max.x) * 2.0f - 1.0f) * aspect_ratio;
				direction.y = ((float)y / (float)scene->screen_max.y) * 2.0f - 1.0f;
				direction.z = -1.0f;
				temp = plane_intersect(scene, &direction, &scene->object);
				a = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
				b = 2.0f * (origin.x * direction.x + origin.y * direction.y + origin.z * direction.z);
				c = origin.x * origin.x + origin.y * origin.y + \
						origin.z * origin.z - scene->object.radius2;
				discriminant = b * b - 4.0f * a * c;
				if (discriminant >= 0.0f)
				{
					t0 = (-b - sqrt(discriminant)) / (2.0f * a);
					if (discriminant > 0.0f)
						t1 = (-b + sqrt(discriminant)) / (2.0f * a);
					if (t0 < 0.0f)
					{
						t0 = t1;
					//	if (t0 < 0.0f)
					//		t0 = 0.0f;
					}
					//from camera
					/*
					intersection.x = ((1 - t0) * scene->camera.x) + t0 * direction.x;
					intersection.y = ((1 - t0) * scene->camera.y) + t0 * direction.y;
					intersection.z = ((1 - t0) * scene->camera.z) + t0 * direction.z;
					*/
					//from zero
					color.color = scene->object.color.color;
					intersection.x = scene->camera.x + t0 * direction.x;
					intersection.y = scene->camera.y + t0 * direction.y;
					intersection.z = scene->camera.z + t0 * direction.z;
					//Do light version using dot product
					normal = vec_minus(intersection, scene->object.position);
					normal = normalize(normal);
					angle = get_angle(normal, scene->light);
					angle = 1.0 - ft_norm(angle, 0.0f, 1.57079f);
					if	(angle < 0)
					{
						color.rgb[0] += ((float)color.rgb[0]) * angle;
						color.rgb[1] += ((float)color.rgb[1]) * angle;
						color.rgb[2] += ((float)color.rgb[2]) * angle;
					}
					else
					{
						color.rgb[0] += (255.0f - (float)color.rgb[0]) * angle;
						color.rgb[1] += (255.0f - (float)color.rgb[1]) * angle;
						color.rgb[2] += (255.0f - (float)color.rgb[2]) * angle;
					}
					data->map.ptr[y][x] = color.color;
				}
				else if (temp < t0)
				{
					data->map.ptr[y][x] = scene->object.plane.color;
				}
				else
					data->map.ptr[y][x] = 0x222222;
				x++;
			}
			y++;
	}
}

				/*
				length = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
				direction.x = temp.x/length;
				direction.y = temp.y/length;
				direction.z = -1.0f/lenght;
				map[y][x] = ray_trace(scene, scene->camera, direction);
				*/
