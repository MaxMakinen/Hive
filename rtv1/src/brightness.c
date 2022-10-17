/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brightness.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:58:05 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 10:46:00 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_rgb	color_mult(t_rgb color, double num)
{
	color.rgb[0] *= num;
	color.rgb[1] *= num;
	color.rgb[2] *= num;
	return (color);
}

t_rgb	mix(t_rgb color, t_rgb color2, double mix_value)
{
	color = color_mult(color, 1 - mix_value);
	color2 = color_mult(color2, mix_value);
	color.rgb[0] += color2.rgb[0];
	color.rgb[1] += color2.rgb[1];
	color.rgb[2] += color2.rgb[2];
	return (color);
}

t_rgb	pattern_at(t_pattern pattern, t_vec2f map)
{
	int	u2;
	int	v2;

	u2 = ft_floor(map.u * pattern.width);
	v2 = ft_floor(map.v * pattern.height);
	if ((u2 + v2) % 2 == 0)
		return (pattern.color1);
	else
		return (pattern.color2);
}

int	norm_dot_color(t_data *data, t_vec3f *light, t_hit *hit)
{
	t_vec3f		lightpos;
	double		angle;
	t_rgb		color;

	color = hit->obj->color;
	lightpos = normalize(vec_minus(*light, hit->pos));
	angle = ft_clamp(dot_product(hit->normal, lightpos), 0.0, 1.0);
	if (hit->obj->type == e_sphere)
		color = pattern_at((t_pattern){4.0 * hit->obj->radius, 2.0 * \
		hit->obj->radius, color, color_mult(color, 0.8)}, hit->surface);
	if (hit->obj->type == e_plane)
		color = pattern_at((t_pattern){2, 2, color, color_mult(color, 0.8)}, \
		hit->surface);
	if (hit->obj->type == e_cylinder || hit->obj->type == e_cone)
		color = pattern_at((t_pattern){10.0 * hit->obj->radius, 2, color, \
	color_mult(color, 0.8)}, hit->surface);
	color.rgb[0] *= angle;
	color.rgb[1] *= angle;
	color.rgb[2] *= angle;
	return (color.color);
}
