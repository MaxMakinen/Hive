/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:44:22 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/15 17:45:11 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	intersect_cylinder(t_ray *inc_ray, t_object *s)
{
	static t_abcd	abcd;
	double			t1;
	double			t2;
	t_matrix		inverse_transform;
	t_ray			ray;

	ray = ray_new_no_malloc(inc_ray->orig, inc_ray->dir);
	inverse_transform = matrix_inverse(&s->transform);
	ray = ray_transform(inc_ray, &inverse_transform);
	
	abcd.a = ((ray.dir.s_xyzw.x * ray.dir.s_xyzw.x))
			 + ((ray.dir.s_xyzw.z * ray.dir.s_xyzw.z));
	if (nearly_equal(abcd.a, 0))
		return (0);
	abcd.b = ((2 * ray.orig.s_xyzw.x * ray.dir.s_xyzw.x)
			 + (2 * ray.orig.s_xyzw.z * ray.dir.s_xyzw.z));
	abcd.c = ((ray.orig.s_xyzw.x * ray.orig.s_xyzw.x)
			 + (ray.orig.s_xyzw.z * ray.orig.s_xyzw.z) - 1);
	abcd.d = calc_discriminant(abcd.a, abcd.b, abcd.c);
	if (abcd.d < 0)
		return (0);
	t1 = (-(abcd.b) - sqrt(abcd.d)) / (2 * abcd.a);
	t2 = (-(abcd.b) + sqrt(abcd.d)) / (2 * abcd.a);
	intersection_record(inc_ray, t1, s);
	intersection_record(inc_ray, t2, s);
	return (1);
	
	return (0);
}
