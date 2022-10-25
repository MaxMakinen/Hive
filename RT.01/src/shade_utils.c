/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:20:32 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/14 10:20:33 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3f	gamma_correct(t_vec3f color)
{
	t_vec3f	temp;

	color.x = ft_clamp(color.x, 0, 255);
	color.y = ft_clamp(color.y, 0, 255);
	color.z = ft_clamp(color.z, 0, 255);
	temp.x = pow(color.x, (1 / GAMMA));
	temp.y = pow(color.y, (1 / GAMMA));
	temp.z = pow(color.z, (1 / GAMMA));
	return (temp);
}

t_vec3f	get_pattern(t_hit *hit)
{
	double	u;
	double	v;

	u = 2;
	v = 2;
	if (hit->obj->pattern == 1)
	{
		if (hit->obj->type == e_cone || hit->obj->type == e_cylinder)
			u = hit->obj->radius * 10;
		if (hit->obj->type == e_sphere)
		{
			v = hit->obj->radius * 2;
			u = hit->obj->radius * 4;
		}
		if ((ft_floor(hit->surface.u * u) + \
		ft_floor(hit->surface.v * v)) % 2 == 0)
			return (vec_mult(hit->obj->col, 0.8));
	}
	return (hit->obj->col);
}
