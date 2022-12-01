/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:41:16 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/14 15:54:20 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "object.h"
#include "tuple.h"
#include <math.h>
#include "../include/rt.h"

int	intersect_sphere(t_ray *inc_ray, t_object *s)
{
	static t_abcd	abcd;
	t_vector		sphere_to_ray;
	double			t1;
	double			t2;
	t_matrix		inverse_transform;
	t_ray			ray;

	ray = ray_new_no_malloc(inc_ray->orig, inc_ray->dir);
	inverse_transform = matrix_inverse(&s->transform);
	ray = ray_transform(inc_ray, &inverse_transform);
	sphere_to_ray = tuple_sub(ray.orig, point_new(0, 0, 0));
	abcd.a = vector_dot(ray.dir, ray.dir);
	abcd.b = 2 * vector_dot(ray.dir, sphere_to_ray);
	abcd.c = vector_dot(sphere_to_ray, sphere_to_ray) - 1;
	abcd.d = calc_discriminant(abcd.a, abcd.b, abcd.c);
	if (abcd.d < 0)
		return (0);
	t1 = (-(abcd.b) - sqrt(abcd.d)) / (2 * abcd.a);
	t2 = (-(abcd.b) + sqrt(abcd.d)) / (2 * abcd.a);
	//printf("%f %f\n", t1, t2);
	// intersection_record_test(inc_ray, t1, t2, s);
	// printf("o xs: %f %f\n", t1, t2);
	intersection_record(inc_ray, t1, s);
	intersection_record(inc_ray, t2, s);
	return (1);
}
