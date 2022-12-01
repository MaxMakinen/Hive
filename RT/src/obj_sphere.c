/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:28:21 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/07 17:09:15 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_tuple	get_sphere_normal(t_main *main, t_hit_record *hit)
{
	t_tuple	result;

	result = tuple_scalar_mult(main->ray.dir, hit->hit_dist);
	result = tuple_add(main->ray.orig, result);
	result = tuple_sub(result, main->obj[main->ray.hit.clo_obj_id].loc);
	result = tuple_unit(result);
	return (result);
}

	// tc = distance along ray closest to sphere center
	// if tc is negative we're looking in the wrong direction
	// d = distance from sphere center to t
	// our ray, so one again pythagoras gives us the closest intersection
	// so, once again
	// d = distance to ray from sphere center
	// if intersection point behind projection plane
	// we now know sphere radius and closest point to sphere center along
	// tc = distance to closest point perpendicular to sphere 
			// center from ray origin
	// tp = distance from d to sphere surface
	// if d is greater than radius of sphere there is no intersection

double	intersects_sphere(t_ray *ray, t_object *sphere)
{
	t_tuple	ray_origin_to_sphere;
	double	distance_to_intersection;
	double	b2_4ac;
	t_abc	abc;

	ray_origin_to_sphere = tuple_sub(ray->orig, sphere->loc);
	abc.a = vector_dot(ray->dir, ray->dir);
	abc.b = (2 * vector_dot(ray->dir, ray_origin_to_sphere));
	abc.c = (vector_dot(ray_origin_to_sphere, ray_origin_to_sphere)
			- (sphere->size * sphere->size));
	b2_4ac = calc_b2_4ac(abc);
	if (b2_4ac > 0)
	{
		distance_to_intersection = quadratic(abc, b2_4ac);
		return (distance_to_intersection);
	}
	return (-1.0);
}
