/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_surface_coordinates.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:42:54 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 09:42:56 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec2f	get_spherical(t_obj *obj, t_vec3f rotated)
{
	t_vec2f	map;

	rotated = normalize(rotated);
	map.u = (1 + atan2(rotated.z, rotated.x) / M_PI) * 0.5;
	map.v = acos(rotated.y) / M_PI;
	return (map);
}

t_vec2f	get_planar(t_vec3f rotated)
{
	return ((t_vec2f){fmod(rotated.x, 1.0), fmod(rotated.z, 1.0)});
}

t_vec2f	get_cylindrical(t_vec3f rotated)
{
	t_vec2f	polar;

	polar.u = 1 - (atan2(rotated.x, rotated.z) / (2 * M_PI) + 0.5);
	polar.v = rotated.y - ft_floor(rotated.y);
	return (polar);
}
