/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:29:24 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/28 14:37:32 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static t_abc	
	calc_abc_cone(t_vec3 raydir, t_vec3 conedir, t_vec3 raycyl, double radius)
{
	t_abc	abc;
	double	rr;

	rr = radius * radius;
	conedir = vec3_unit(conedir);
	abc.a = 1 - rr * vec3_dot(raydir, conedir) * vec3_dot(raydir, conedir)
		- vec3_dot(raydir, conedir) * vec3_dot(raydir, conedir);
	abc.b = 2 * (vec3_dot(raydir, raycyl) - rr * vec3_dot(raydir, conedir)
			* vec3_dot(raycyl, conedir) - vec3_dot(raydir, conedir)
			* vec3_dot(raycyl, conedir));
	abc.c = vec3_dot(raycyl, raycyl) - rr * vec3_dot(raycyl, conedir)
		* vec3_dot(raycyl, conedir) - vec3_dot(raycyl, conedir)
		* vec3_dot(raycyl, conedir);
	return (abc);
}

t_vec3	get_cone_normal(t_main *main, t_hit_record *hit)
{
	t_vec3	result;
	t_vec3	hypotenuse;

	hit->hit_loc = vec3_ray_at(main->ray, hit->hit_dist);
	hypotenuse = vec3_sub(hit->hit_loc, main->obj[hit->clo_obj_id].loc);
	result = vec3_unit(vec3_cross(hypotenuse,
				vec3_cross(hypotenuse, main->obj[hit->clo_obj_id].rot)));
	if (vec3_dot(main->ray.dir, result) > 0)
		result = vec3_neg(result);
	return (result);
}

double	intersects_cone(t_ray *ray, t_object *cone)
{
	t_vec3	ray_cone;
	t_abc	abc;
	double	b2_4ac;

	ray_cone = vec3_sub(ray->orig, cone->loc);
	abc = calc_abc_cone(ray->dir, cone->rot, ray_cone, cone->size);
	b2_4ac = calc_b2_4ac(abc);
	if (b2_4ac > 0)
		return (quadratic(abc, b2_4ac));
	return (-1);
}
