/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:29:24 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/07 17:04:33 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static t_abc	
	calc_abc_cone(t_tuple raydir, t_tuple conedir, t_tuple raycyl, double radius)
{
	t_abc	abc;
	double	rr;

	rr = radius * radius;
	conedir = tuple_unit(conedir);
	abc.a = 1 - rr * vector_dot(raydir, conedir) * vector_dot(raydir, conedir)
		- vector_dot(raydir, conedir) * vector_dot(raydir, conedir);
	abc.b = 2 * (vector_dot(raydir, raycyl) - rr * vector_dot(raydir, conedir)
			* vector_dot(raycyl, conedir) - vector_dot(raydir, conedir)
			* vector_dot(raycyl, conedir));
	abc.c = vector_dot(raycyl, raycyl) - rr * vector_dot(raycyl, conedir)
		* vector_dot(raycyl, conedir) - vector_dot(raycyl, conedir)
		* vector_dot(raycyl, conedir);
	return (abc);
}

t_tuple	get_cone_normal(t_main *main, t_hit_record *hit)
{
	t_tuple	result;
	t_tuple	hypotenuse;

	hit->hit_loc = ray_position(main->ray, hit->hit_dist);
	hypotenuse = tuple_sub(hit->hit_loc, main->obj[hit->clo_obj_id].loc);
	result = tuple_unit(vector_cross(hypotenuse,
				vector_cross(hypotenuse, main->obj[hit->clo_obj_id].rot)));
	if (vector_dot(main->ray.dir, result) > 0)
		result = tuple_neg(result);
	return (result);
}

double	intersects_cone(t_ray *ray, t_object *cone)
{
	t_tuple	ray_cone;
	t_abc	abc;
	double	b2_4ac;

	ray_cone = tuple_sub(ray->orig, cone->loc);
	abc = calc_abc_cone(ray->dir, cone->rot, ray_cone, cone->size);
	b2_4ac = calc_b2_4ac(abc);
	if (b2_4ac > 0)
		return (quadratic(abc, b2_4ac));
	return (-1);
}
