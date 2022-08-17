/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:13:09 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/17 15:25:26 by mmakinen         ###   ########.fr       */
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

int	plane_intersect(t_scene *scene, t_vec3f origin, t_vec3f direction, t_vec3f normal, float *intersect)
{
	float	denominator;

	denominator = dot_product(normal, direction);
	if (fabs(denominator) > 0.000001f)
	{
		*intersect = dot_product(origin, normal) / denominator;
		if (*intersect >= 0)
			return (TRUE);
	}
	return (FALSE);
}

int	cylinder_intersect(t_scene *scene, t_vec3f direction, t_object *object, float *intersect)
{
	float		a;
	float		b;
	float		c;
	float		t0;
	float		t1;
	float		discriminant;
	t_vec3f		origin;

	t0 = 0.0f;
	origin = vec_minus(scene->camera, object->cylinder_pos);
	a = direction.x * direction.x + direction.z * direction.z;
	b = 2.0f * (origin.x * direction.x + origin.z * direction.z);
	c = (origin.x * origin.x + origin.z * origin.z) - object->cylinder_radius2;
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
}

/*MAKE FUNCTION FOR QUADRTIC FORMULA! many intersect formulas use it*/
int	sphere_intersect(t_scene *scene, t_vec3f origin, t_vec3f direction, float radius2, float *t0)
{
	float		a;
	float		b;
	float		c;
	float		t1;
	float		discriminant;

	a = dot_product(direction, direction);
	b = 2.0f * dot_product(origin, direction);
	c = dot_product(origin, origin) - radius2;
	discriminant = b * b - 4.0f * a * c;
	if (discriminant >= 0.0f)
	{
		*t0 = (-b - sqrt(discriminant)) / (2.0f * a);
		if (discriminant > 0.0f)
			t1 = (-b + sqrt(discriminant)) / (2.0f * a);
		if (*t0 <= 0.0f)
		{
			*t0 = t1;
			if (*t0 <= 0.0f)
				return(FALSE);
		}
		return (*t0);
	}
	return (FALSE);
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
				if (plane_intersect(scene, vec_minus(scene->object.plane_orig, scene->camera), direction, scene->object.plane_normal, &temp))
				{
					if (temp < closest || closest == 0.0f)
					{
						closest = temp;
						type = 1;
					}
				}
				if (sphere_intersect(scene, vec_minus(scene->camera, scene->object.sphere_pos), direction, scene->object.radius2, &temp))
				{
					if (temp < closest || closest == 0.0f)
					{
						closest = temp;
						type = 2;
					}
				}
//				if (cylinder_intersect(scene, direction, &scene->object, &cylinder))
//					hitpoint_cyl = get_intersect(scene->camera, direction, cylinder);
				intersection = get_intersect(scene->camera, direction, closest);
				if (type == 1)
				{
					color = &scene->object.plane;
					normal = scene->object.plane_normal;
					intersection = vec_plus(intersection, vec_mult(normal, BIAS));
				}
				else
				{
					if (tp == 0)
					{
						printf("shadow intersect = %f\nintersection.x = %f\nintersection.y = %f\nintersection.z = %f\n", closest, intersection.x, intersection.y, intersection.z);
						tp = 2;
					}
					color = &scene->object.sphere;
					normal = vec_minus(intersection, scene->object.sphere_pos);
					intersection = vec_plus(intersection, vec_mult(normal, BIAS));
					if (tp == 2)
					{
						printf("shadow intersect = %f\nintersection.x = %f\nintersection.y = %f\nintersection.z = %f\n", closest, intersection.x, intersection.y, intersection.z);
						tp = 3;
					}
				}
				int	shadow;
				if (closest > 0.0f)
				{
					shadow = 0;
//					intersection = vec_plus(scene->camera, direction, closest));
					direction = vec_minus(scene->light, intersection);
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
						if (sphere_intersect(scene, vec_minus(intersection, scene->object.sphere_pos), direction, scene->object.radius2, &temp))
						{
							if (tp == 4 && temp < 2)
							{
								printf("shadow intersect = %f\nintersection.x = %f\nintersection.y = %f\nintersection.z = %f\n", temp, intersection.x, intersection.y, intersection.z);
								tp = 12;
							}
							shadow = 2;
							data->map.ptr[y][x] = 0;
						}
					}
					if (!shadow)
						angle_color(data, scene, intersection, x, y, *color, normal);
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
