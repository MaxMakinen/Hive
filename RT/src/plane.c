/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:23:05 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/17 15:43:31 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	intersect_plane(t_ray *inc_ray, t_object *s)
{
	//t_vector		plane_to_ray;
/* 	t_tuple			hit_loc; */
	double			t;
	t_matrix		inverse_transform;
	t_ray			ray;

	ray = ray_new_no_malloc(inc_ray->orig, inc_ray->dir);
	inverse_transform = matrix_inverse(&s->transform);
	ray = ray_transform(inc_ray, &inverse_transform);
	//plane_to_ray = tuple_sub(ray.orig, point_new(0, 0, 0));
	if (fabs(ray.dir.s_xyzw.y) < EPSILON)
		return (0);
	t = ((-ray.orig.s_xyzw.y) / ray.dir.s_xyzw.y);
	/* hit_loc = ray_position(ray, t); */
	if (t < 0 )/* || hit_loc.s_xyzw.x > 1 || hit_loc.s_xyzw.x < -1
			|| hit_loc.s_xyzw.z > 1 || hit_loc.s_xyzw.z < -1) */
	return (0);
	intersection_record(inc_ray, t, s);
	return (1);
}
