/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_shadowed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:43:31 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/15 14:44:00 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	is_shadowed(t_scene *scene, t_light light, t_point point)
{
	t_vector		to_light;
	double			distance;
	t_vector		direction;
	t_intersection	intersection;
	t_ray			ray;

	to_light = tuple_sub(light.location, point);
	distance = tuple_mag(to_light);
	direction = tuple_unit(to_light);
	ray = ray_new(point, direction);
	scene_intersect(scene, &ray);
	if (ray.xs.vec.len == 0)
	{
		vec_free(&ray.xs.vec);
		return (0);
	}
	intersection = find_closest_intersection(&ray.xs);
	// vec_free(&ray.xs.vec);
	if (intersection.t < distance && intersection.t > 0)
		return (1);
	return (0);
}
