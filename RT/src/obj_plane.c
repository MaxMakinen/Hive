/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 20:22:17 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/20 11:24:13 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	fix_normal(t_ray *ray, t_object *plane)
{
	double	temp;

	temp = sqrt((vec3_dot(plane->rot, plane->rot)));
	div_vect_float(plane->rot, temp);
	temp = vec3_dot(plane->rot, ray->dir);
	if (temp < 0)
		plane->rot = div_vect_float(plane->rot, -1.0);
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
	t_vec3		n;
	t_vec3		abc;

	fix_normal(ray, plane);
	n = plane->rot;
	intersection = vec3_dot(ray->dir, n);
	abc = vec3_sub(ray->orig, plane->loc);
	abc.x *= -1.0;
	abc.y *= -1.0;
	abc.z *= -1.0;
	t = (vec3_dot(abc, n) / intersection);
	if (intersection != 0 && t > 0)
		return (t);
	return (-1);
}
