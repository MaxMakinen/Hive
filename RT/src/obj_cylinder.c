/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:45:46 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/28 14:39:02 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static t_abc	calc_abc_cylinder(t_ray ray,
								t_vec3 cyldir,
								t_vec3 raycyl,
								double radius)
{
	t_abc	abc;

	abc.a = 1 - vec3_dot(ray.dir, cyldir) * vec3_dot(ray.dir, cyldir);
	abc.b = 2 * (vec3_dot(ray.dir, raycyl) - vec3_dot(ray.dir, cyldir)
			* vec3_dot(raycyl, cyldir));
	abc.c = vec3_dot(raycyl, raycyl) - vec3_dot(raycyl, cyldir)
		* vec3_dot(raycyl, cyldir) - radius * radius;
	return (abc);
}

t_vec3	get_cylinder_normal(t_main *main, t_hit_record *hit)
{
	t_vec3	result;
	t_vec3	hypotenuse;

	hypotenuse = (vec3_sub(hit->hit_loc, main->obj[hit->clo_obj_id].loc));
	result = vec3_unit(vec3_cross(main->obj[hit->clo_obj_id].rot,
				vec3_cross(hypotenuse, main->obj[hit->clo_obj_id].rot)));
	return (result);
}

double	intersects_cylinder(t_ray *ray, t_object *cylinder)
{
	t_vec3	ray_cyl;
	t_abc	abc;
	double	b2_4ac;

	ray_cyl = vec3_sub(ray->orig, cylinder->loc);
	cylinder->rot = vec3_unit(cylinder->rot);
	abc = calc_abc_cylinder(*ray, cylinder->rot, ray_cyl, cylinder->size);
	b2_4ac = calc_b2_4ac(abc);
	if (b2_4ac > 0)
		return (quadratic(abc, b2_4ac));
	return (-1);
}
