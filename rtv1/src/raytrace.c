/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:13:09 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/08 11:49:30 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	dot_product(t_vec3f vec1, t_vec3f vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

double	vec_len(t_vec3f vec)
{
	return (sqrt(dot_product(vec, vec)));
}

t_vec3f	normalize(t_vec3f vec)
{
	double	magnitude;

	magnitude = vec_len(vec);
	vec.x /= magnitude;
	vec.y /= magnitude;
	vec.z /= magnitude;
	return (vec);
}

t_vec3f	cross_product(t_vec3f vec1, t_vec3f vec2)
{
	t_vec3f	answer;

	answer.x = vec1.y * vec2.z - vec1.z * vec2.y;
	answer.y = vec1.z * vec2.x - vec1.x * vec2.z;
	answer.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (answer);
}

float	get_angle(t_vec3f vec1, t_vec3f vec2)
{
	return (acos(dot_product(vec1, vec2) / (vec_len(vec1) * vec_len(vec2))));
}

t_vec3f	get_intersect(t_vec3f origin, t_vec3f direction, float distance)
{
	t_vec3f	intersect;

	intersect.x = origin.x + direction.x * distance;
	intersect.y = origin.y + direction.y * distance;
	intersect.z = origin.z + direction.z * distance;
	return (intersect);
}

t_vec3f	vec_minus(t_vec3f vec1, t_vec3f vec2)
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
	//a = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
	//b = 2.0f * (origin.x * direction.x + origin.y * direction.y + origin.z * direction.z);
	//c = origin.x * origin.x + origin.y * origin.y + origin.z * origin.z - object->radius2;

void	angle_color(t_data *data, t_scene *scene, t_vec3f intersection, int x, int y, t_rgb color, t_vec3f normal)
{
	float	angle;
	float	midway;
	t_vec3f	light;

	light = vec_minus(scene->light, intersection);
	normal = normalize(normal);
	angle = get_angle(normal, light);
	angle = fabs(angle);
	midway = 90.0f * (M_PI / 180.0f);
	angle = 1.0f - ft_norm(angle, 0.0f, midway);
	if (angle <= 0.01f)
		angle = -1.0f;
//	if	(angle < 0)
//	{
		color.rgb[0] += (unsigned char)((float)color.rgb[0]) * angle;
		color.rgb[1] += (unsigned char)((float)color.rgb[1]) * angle;
		color.rgb[2] += (unsigned char)((float)color.rgb[2]) * angle;
/*	}
	else
	{
		color.rgb[0] += (255.0f - (float)color.rgb[0]) * angle;
		color.rgb[1] += (255.0f - (float)color.rgb[1]) * angle;
		color.rgb[2] += (255.0f - (float)color.rgb[2]) * angle;
	}
*/	data->map.ptr[y][x] = color.color;
}

//Color should be defining a brightness value. Later brightness is used to edit our color.

/* We use the normal of the hit point on the sphere to calculate a color.
 * The normal gets normalized to between -1 and 1, 
 * and then further scaled to between 0 and 1 for the color calculation. */
void	norm_color(t_data *data, t_scene *scene, t_vec3f hit_pos, int x, int y)
{
	t_rgb		color;
	t_vec3f		normal;

	color.color = 0;
	normal = vec_minus(hit_pos, scene->object.sphere_pos);
	normal = normalize(normal);
	color.rgb[0] = (unsigned char)((normal.x * 0.5f + 0.5f) * 255.0);
	color.rgb[1] = (unsigned char)((normal.y * 0.5f + 0.5f) * 255.0);
	color.rgb[2] = (unsigned char)((normal.z * 0.5f + 0.5f) * 255.0);
	color.rgb[3] = 0xff;
	data->map.ptr[y][x] = color.color;
}

void	norm_dot_color(t_data *data, t_scene *scene, t_vec3f hit_pos, int x, int y, t_rgb color, t_vec3f normal)
{
	t_vec3f		lightdir;
	double		angle;

	normal = normalize(normal);
	lightdir = normalize(scene->light);
	angle = dot_product(normal, lightdir);

	if	(angle < 0)
	{
		color.rgb[0] += (unsigned char)((float)color.rgb[0]) * angle;
		color.rgb[1] += (unsigned char)((float)color.rgb[1]) * angle;
		color.rgb[2] += (unsigned char)((float)color.rgb[2]) * angle;
	}
	else
	{
		color.rgb[0] += (unsigned char)(255.0f - (float)color.rgb[0]) * angle;
		color.rgb[1] += (unsigned char)(255.0f - (float)color.rgb[1]) * angle;
		color.rgb[2] += (unsigned char)(255.0f - (float)color.rgb[2]) * angle;
	}
	data->map.ptr[y][x] = color.color;
}

int	plane_intersect(t_scene *scene, t_vec3f direction, t_object *object, float *intersect)
{
	float	denominator;
	t_vec3f	origin;
	t_vec3f	normal;

	normal = object->plane_normal;
	denominator = dot_product(normal, direction);
	if (fabs(denominator) > 0.000001f)
	{
		origin = vec_minus(object->plane_orig, scene->camera);
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

int	sphere_intersect(t_scene *scene, t_vec3f direction, t_object *object, float *t0)
{
	float		a;
	float		b;
	float		c;
	float		t1;
	float		discriminant;
	t_vec3f		origin;

	origin = vec_minus(scene->camera, object->sphere_pos);
	a = dot_product(direction, direction);
	b = 2.0f * dot_product(origin, direction);
	c = dot_product(origin, origin) - object->radius2;
	discriminant = b * b - 4.0f * a * c;
	if (discriminant >= 0.0f)
	{
		*t0 = (-b - sqrt(discriminant)) / (2.0f * a);
		if (discriminant > 0.0f)
			t1 = (-b + sqrt(discriminant)) / (2.0f * a);
		if (*t0 < 0.0f)
		{
			*t0 = t1;
			if (*t0 < 0.0f)
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
	float		temp;
	float		closest;
	int 		type;
	t_rgb		*color;

	temp = 0.0f;
	y = data->screen_min.y;
	while (y < data->screen_max.y)
	{
		x = data->screen_min.x;
			while (x < data->screen_max.x)
			{
				closest = 0.0f;
				direction = get_direction(data, (float)x, (float)y);
				if (plane_intersect(scene, direction, &scene->object, &temp))
				{
					if (temp < closest || closest == 0.0f)
					{
						closest = temp;
						type = 1;
					}
				}
				if (sphere_intersect(scene, direction, &scene->object, &temp))
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
				}
				else
				{
					color = &scene->object.sphere;
					normal = vec_minus(intersection, scene->object.sphere_pos);
				}
				if (closest > 0.0f)
				{
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
