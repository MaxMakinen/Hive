/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brightness.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:58:05 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/31 14:46:51 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	norm_dot_color(t_data *data, t_vec3f *light, t_vec3f intersection, int x, int y, t_rgb color, t_vec3f normal)
{
	t_vec3f		lightpos;
	double		angle;

	lightpos = normalize(vec_minus(*light, intersection));
	angle = ft_clamp(dot_product(normal, lightpos), 0.0, 1.0);
	color.rgb[0] *= angle;
	color.rgb[1] *= angle;
	color.rgb[2] *= angle;		
	data->map.ptr[y][x] = color.color;
}
