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

void	get_box(t_obj *object, t_hit *hit)
{
	t_vec3f	temp;
	t_vec3f	sign;

	temp = vec_minus(hit->pos, object->pos);
	
	sign.x = 1;
	sign.y = 1;
	sign.z = 1;

	if (temp.x < 0)
		sign.x = -1;
	if (temp.y < 0)
		sign.y = -1;
	if (temp.z < 0)
		sign.z = -1;
	if (fabs(temp.x - object->bb_max.x) < EPSILON)
		hit->normal = (t_vec3f){1.0, 0.0, 0.0};
	if (fabs(temp.x - object->bb_min.x) < EPSILON)
		hit->normal = (t_vec3f){-1.0, 0.0, 0.0};
	
	else if (fabs(temp.y - object->bb_max.y) < EPSILON)
		hit->normal = (t_vec3f){0.0, 1.0, 0.0};
	else if (fabs(temp.y - object->bb_min.y) < EPSILON)
		hit->normal = (t_vec3f){0.0, -1.0, 0.0};
	
	else if (fabs(temp.z - object->bb_max.z) < EPSILON)
		hit->normal = (t_vec3f){0.0, 0.0, 1.0};
	else if (fabs(temp.z - object->bb_min.z) < EPSILON)
		hit->normal = (t_vec3f){0.0, 0.0, -1.0};
	hit->normal = normalize(hit->normal);
	
}

void	get_normal(t_obj *object, t_hit *hit, t_ray *ray)
{
	rotate(object, hit);
	if (object->type == e_plane || object->type == e_disc)
		get_plane(object, hit);
	else if (object->type == e_sphere)
		get_sphere(object, hit);
	else if (object->type == e_cylinder)
		get_cylinder(object, hit);
	else if (object->type == e_cone)
		get_cone(object, hit);
	else if (object->type == e_box)
		get_box(object, hit);
	if (dot_product(hit->normal, ray->dir) > 0)
		hit->normal = vec_mult(hit->normal, -1.0);
	hit->pos = vec_plus(hit->pos, vec_mult(hit->normal, BIAS));
}
