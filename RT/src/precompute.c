/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:04:17 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/14 20:14:41 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_hit_record	precompute(t_intersection *intersection, t_ray *ray)
{
	t_hit_record	hit;

	hit.hit_dist = intersection->t;
	hit.object = intersection->object;
	hit.hit_loc = ray_position(*ray, hit.hit_dist);
	hit.to_eye = tuple_neg(ray->dir);
	hit.normal = normal_at(hit.object, hit.hit_loc);
	if (vector_dot(hit.normal, hit.to_eye) < 0)
	{
		hit.inside = 1;
		hit.normal = tuple_neg(hit.normal);
	}
	else
		hit.inside = 0;
	return (hit);
}