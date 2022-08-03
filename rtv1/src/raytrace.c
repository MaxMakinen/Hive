/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:13:09 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/03 21:36:45 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

t_map	make_image(t_scene *scene)
{
	int			x;
	int			y;
	float		lenght;
	t_3vec		direction;
	t_3vec		temp;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_map		map;
	int			*itemp;

	map.pool = (int *)ft_calloc(WINDOW_WIDTH * WINDOW_HEIGHT, sizeof(int));
	map.ptr = (int **)ft_calloc(WINDOW_HEIGHT, sizeof(int *));
	itemp = map.pool;
	x = 0;
	while (x < WINDOW_HEIGHT)
	{
		map.ptr[x] = itemp;
		itemp += WINDOW_WIDTH;
		x++;
	}

	y = scene->screen_min.y;
	while (y < scene->screen_max.y)
	{
		x = scene->screen_min.x;
			while (x < scene->screen_max.x)
			{
				temp.x = ((float)x / (float)scene->screen_max.x) * 2.0f - 1.0f;
				temp.y = ((float)y / (float)scene->screen_max.y) * 2.0f - 1.0f;
				temp.z = -1.0f;
				a = temp.x * temp.x + temp.y * temp.y + temp.z * temp.z;
				b = 2.0f * (scene->camera.x * temp.x + scene->camera.y * temp.y + scene->camera.z * temp.z);
				c = scene->camera.x * scene->camera.x + scene->camera.y * scene->camera.y + \
						scene->camera.z * scene->camera.z - scene->radius * scene->radius;
				discriminant = b * b - 4.0f * a * c;
				if (discriminant >= 0)
					map.ptr[y][x] = 0xffff00ff;
				else
					map.ptr[y][x] = 0x222222;
				x++;
			}
			y++;
	}
	return (map);
}

				/*
				length = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
				direction.x = temp.x/length;
				direction.y = temp.y/length;
				direction.z = -1.0f/lenght;
				map[y][x] = ray_trace(scene, scene->camera, direction);
				*/
