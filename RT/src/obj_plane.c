/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 20:22:17 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/10 18:54:28 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	fix_normal(t_ray *ray, t_object *plane)
{
	double	temp;

	temp = sqrt((vector_dot(plane->rot, plane->rot)));
	tuple_scalar_div(plane->rot, temp);
	temp = vector_dot(plane->rot, ray->dir);
	if (temp < 0)
		plane->rot = tuple_scalar_div(plane->rot, -1.0);
}

/*
Ray and plane intersection
T = Taso = plane.loc
N = Plane normal, plane.rot
P = A point on the plane
R = ray with a start position, R.p, and a direction, R.d.
N • (P - T) = 0
N • P - N • T = 0
and
P = R.p + t * R.d
so
N • (R.p + t * R.d) - N • T = 0
N • (R.p + t * R.d) = N • T
N • R.p + t * (N • R.d) = N • T
t * (N • R.d) = N • T - N • R.p
t = (N • T - N • R.p) /  (N • R.d)
t = (N • (T - R.p)) /  (N • R.d)
*/

double	intersects_plane(t_ray *ray, t_object *plane)
{
	double		intersection;
	double		t;
	t_tuple		n;
	t_tuple		abc;

	fix_normal(ray, plane);
	n = plane->rot;
	intersection = vector_dot(ray->dir, n);
	abc = tuple_sub(ray->orig, plane->loc);
	// abc.s_xyzw.x *= -1.0;
	// abc.s_xyzw.y *= -1.0;
	// abc.s_xyzw.z *= -1.0;
	tuple_neg(abc);
	t = (vector_dot(abc, n) / intersection);
	if (intersection != 0 && t > 0)
		return (t);
	return (-1);
}
