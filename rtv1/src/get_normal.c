/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_surface.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:39:22 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 09:39:28 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_plane(t_obj *object, t_hit *hit)
{
	hit->surface = get_planar(hit->rotated);
	hit->normal = normalize(object->dir);
}

void	get_sphere(t_obj *object, t_hit *hit)
{
	hit->normal = normalize(vec_minus(hit->pos, object->pos));
	hit->surface = get_spherical(object, hit->rotated);
}

void	get_cylinder(t_obj *object, t_hit *hit)
{
	hit->surface = get_cylindrical(hit->rotated);
	hit->normal = normalize(vec_minus(hit->pos, object->pos));
	hit->normal = normalize(cross_product(hit->normal, object->dir));
	hit->normal = normalize(cross_product(object->dir, hit->normal));
}

void	get_cone(t_obj *object, t_hit *hit)
{
	hit->surface = get_cylindrical(hit->rotated);
	hit->normal = normalize(vec_minus(hit->pos, object->pos));
	hit->normal = normalize(cross_product(hit->normal, object->dir));
	hit->normal = normalize(cross_product(object->dir, hit->normal));
	hit->normal.y *= object->radius / object->height;
}

t_hit	*get_normal(t_obj *object, t_hit *hit, t_ray *ray)
{
	rotate(object, hit);
	if (object->type == e_plane)
		get_plane(object, hit);
	else if (object->type == e_sphere)
		get_sphere(object, hit);
	else if (object->type == e_cylinder)
		get_cylinder(object, hit);
	else if (object->type == e_cone)
		get_cone(object, hit);
	if (dot_product(hit->normal, ray->dir) > 0)
		hit->normal = vec_mult(hit->normal, -1.0);
	hit->pos = vec_plus(hit->pos, vec_mult(hit->normal, BIAS));
	return (hit);
}
