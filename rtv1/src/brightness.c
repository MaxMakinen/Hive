/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brightness.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:58:05 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/26 14:23:26 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	color.rgb[3] = 0;
	data->map.ptr[y][x] = color.color;
}

void	norm_dot_color(t_data *data, t_scene *scene, t_vec3f intersection, int x, int y, t_rgb color, t_vec3f normal)
{
	t_vec3f		lightdir;
	t_vec3f		light;
	double		angle;

	light = vec_minus(scene->light, intersection);
	normal = normalize(normal);
	lightdir = normalize(light);
	angle = dot_product(normal, lightdir);
	if (angle < 0.01f)
		angle = -1;

//	if	(angle < 0)
//	{
		color.rgb[0] += (unsigned char)((float)color.rgb[0]) * angle;
		color.rgb[1] += (unsigned char)((float)color.rgb[1]) * angle;
		color.rgb[2] += (unsigned char)((float)color.rgb[2]) * angle;
/*	}
	else
	{
		color.rgb[0] += (unsigned char)(255.0f - (float)color.rgb[0]) * angle;
		color.rgb[1] += (unsigned char)(255.0f - (float)color.rgb[1]) * angle;
		color.rgb[2] += (unsigned char)(255.0f - (float)color.rgb[2]) * angle;
	}
*/	data->map.ptr[y][x] = color.color;
}
