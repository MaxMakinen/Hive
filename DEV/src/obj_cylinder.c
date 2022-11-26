/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:45:46 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/09 16:13:28 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static t_abc	calc_abc_cylinder(t_ray ray,
								t_tuple cyldir,
								t_tuple raycyl,
								double radius)
{
	t_abc	abc;

	abc.a = 1 - vector_dot(ray.dir, cyldir) * vector_dot(ray.dir, cyldir);
	abc.b = 2 * (vector_dot(ray.dir, raycyl) - vector_dot(ray.dir, cyldir)
			* vector_dot(raycyl, cyldir));
	abc.c = vector_dot(raycyl, raycyl) - vector_dot(raycyl, cyldir)
		* vector_dot(raycyl, cyldir) - radius * radius;
	return (abc);
}

t_tuple	get_cylinder_normal(t_main *main, t_hit_record *hit)
{
	t_tuple	result;
	t_tuple	hypotenuse;

	hypotenuse = (tuple_sub(hit->hit_loc, main->obj[hit->clo_obj_id].loc));
	result = tuple_unit(vector_cross(main->obj[hit->clo_obj_id].rot,
				vector_cross(hypotenuse, main->obj[hit->clo_obj_id].rot)));
	return (result);
}

double	intersects_cylinder(t_ray *ray, t_object *cylinder)
{
	t_tuple	ray_cyl;
	t_abc	abc;
	double	b2_4ac;

	ray_cyl = tuple_sub(ray->orig, cylinder->loc);
	cylinder->rot = tuple_unit(cylinder->rot);
	abc = calc_abc_cylinder(*ray, cylinder->rot, ray_cyl, cylinder->size);
	b2_4ac = calc_b2_4ac(abc);
	if (b2_4ac > 0)
		return (quadratic(abc, b2_4ac));
	return (-1);
}
