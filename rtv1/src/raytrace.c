/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:13:09 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/06 23:29:36 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	dot_product(t_3vec vec1, t_3vec vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

double	vec_len(t_3vec vec)
{
	return (sqrt(dot_product(vec, vec)));
}

t_3vec	normalize(t_3vec vec)
{
	double	magnitude;

	magnitude = vec_len(vec);
	vec.x /= magnitude;
	vec.y /= magnitude;
	vec.z /= magnitude;
	return (vec);
}

t_3vec	cross_product(t_3vec vec1, t_3vec vec2)
{
	t_3vec	answer;

	answer.x = vec1.y * vec2.z - vec1.z * vec2.y;
	answer.y = vec1.z * vec2.x - vec1.x * vec2.z;
	answer.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (answer);
}

float	get_angle(t_3vec vec1, t_3vec vec2)
{
	return (acos(dot_product(vec1, vec2) / (vec_len(vec1) * vec_len(vec2))));
}

t_3vec	get_intersect(t_3vec origin, t_3vec direction, float distance)
{
	t_3vec	intersect;

	intersect.x = origin.x + direction.x * distance;
	intersect.y = origin.y + direction.y * distance;
	intersect.z = origin.z + direction.z * distance;
	return (intersect);
}

t_3vec	vec_minus(t_3vec vec1, t_3vec vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	vec1.z -= vec2.z;
	return (vec1);
}

t_3vec	vec_mult(t_3vec vec1, float num)
{
	vec1.x *= num;
	vec1.y *= num;
	vec1.z *= num;
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
float	sphere_intersect(t_scene *scene, t_3vec direction, t_object *object)
{
	float		a;
	float		b;
	float		c;
	float		t0;
	float		t1;
	float		discriminant;
	t_3vec		origin;

	origin = vec_minus(scene->camera, object->sphere_pos);
	a = dot_product(direction, direction);
	b = 2.0f * dot_product(origin, direction);
	c = dot_product(origin, origin) - object->radius2;
	discriminant = b * b - 4.0f * a * c;
	if (discriminant >= 0.0f)
	{
		t0 = (-b - sqrt(discriminant)) / (2.0f * a);
		if (discriminant > 0.0f)
			t1 = (-b + sqrt(discriminant)) / (2.0f * a);
		if (t0 < 0.0f)
		{
			t0 = t1;
			if (t0 < 0.0f)
				return(FALSE);
		}
		return (t0);
	}
	return (FALSE);
}

void	sphere_color(t_data *data, t_scene *scene, t_3vec intersection, int x, int y)
{
	t_rgb		color;
	t_3vec		normal;
	double		angle;

	color.color = scene->object.color.color;
	normal = vec_minus(intersection, scene->object.sphere_pos);
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

/* We use the normal of the hit point on the sphere to calculate a color.
 * The normal gets normalized to between -1 and 1, 
 * and then further scaled to between 0 and 1 for the color calculation. */
void	norm_color(t_data *data, t_scene *scene, t_3vec hit_pos, int x, int y)
{
	t_rgb		color;
	t_3vec		normal;

	color.color = 0;
	normal = vec_minus(hit_pos, scene->object.sphere_pos);
	normal = normalize(normal);
	color.rgb[0] = (unsigned char)((normal.x * 0.5f + 0.5f) * 255.0);
	color.rgb[1] = (unsigned char)((normal.y * 0.5f + 0.5f) * 255.0);
	color.rgb[2] = (unsigned char)((normal.z * 0.5f + 0.5f) * 255.0);
	color.rgb[3] = 0xff;
	data->map.ptr[y][x] = color.color;
}

void	norm_dot_color(t_data *data, t_scene *scene, t_3vec hit_pos, int x, int y, t_rgb color, t_3vec normal)
{
	t_3vec		lightdir;
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

float	plane_intersect(t_scene *scene, t_3vec direction, t_object *object, float *intersect)
{
	float	denominator;
	t_3vec	origin;
	t_3vec	normal;

	normal = object->normal;
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

void	make_image(t_scene *scene, t_data *data)
{
	int			x;
	int			y;
	t_3vec		direction;
	t_3vec		intersection;
	float		temp;
	float		temp2;
	float		aspect_ratio;
	float		fov;
	float		scale;
	float		t0;
	t_3vec		hitpoint;
	t_rgb		plane_col;

	aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	int	q = 0;
	y = scene->screen_min.y;
	fov = 39.6f; //40 degrees works. number allegedly copied from blender.
	scale = tan(((fov * 0.5f) * (M_PI / 180)));
	while (y < scene->screen_max.y)
	{
		x = scene->screen_min.x;
			while (x < scene->screen_max.x)
			{
				direction.x = (((2.0f * (((float)x + 0.5f) / (float)scene->screen_max.x)) - 1.0f) * aspect_ratio);
				direction.y = (1.0f - (2.0f * (((float)y + 0.5f) / (float)scene->screen_max.y)));
				direction.x = (((2.0f * (((float)x + 0.5f) / (float)scene->screen_max.x)) - 1.0f) * aspect_ratio) * scale;
				direction.y = (1.0f - (2.0f * (((float)y + 0.5f) / (float)scene->screen_max.y))) * scale;
				direction.z = -1.0f;
				direction = normalize(direction);
				if (plane_intersect(scene, direction, &scene->object, &temp))
				{
					hitpoint = get_intersect(scene->camera, direction, temp);
					/*
					hitpoint.x = scene->camera.x + direction.x * temp;
					hitpoint.y = scene->camera.y + direction.y * temp;
					hitpoint.z = scene->camera.z + direction.z * temp;
					*/
				}
				else
					temp = -1.0f;
				temp2 = sphere_intersect(scene, direction, &scene->object);
				/*
				if (temp >= 0.0f && q < 5)
				{
				//	printf("x = %d dir.x= %f\n", x, direction.x);
					printf("plane temp = %f\n", temp);
					q++;
				}*/
				if (temp2 > 0.0f)
				{
					intersection = get_intersect(scene->camera, direction, temp2);
					/*
					t0 = temp2;
					intersection.x = scene->camera.x + t0 * direction.x;
					intersection.y = scene->camera.y + t0 * direction.y;
					intersection.z = scene->camera.z + t0 * direction.z;
					*/
					//Do light version using dot product
					//sphere_color(data, scene, intersection, x, y);
					norm_dot_color(data, scene, intersection, x, y, scene->object.color, vec_minus(intersection, scene->object.sphere_pos));
				}
				else
					data->map.ptr[y][x] = 0x222222;
				if (temp < temp2 && temp >= 0.0f || temp2 == 0.0f && temp >= 0.0f)
				{
					norm_dot_color(data, scene, hitpoint, x, y, scene->object.plane, scene->object.normal);
					//data->map.ptr[y][x] = scene->object.plane.color;
				}
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
