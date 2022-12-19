/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:57:35 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/14 18:02:38 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	get_shape_intersections(t_ray *ray, t_object *shape)
{
	int	ret;

	ret = 0;
	if (shape->type == SPHERE)
		ret = intersect_sphere(ray, shape);
	else if (shape->type == CYLINDER)
		ret = intersect_cylinder(ray, shape);
	else if (shape->type == PLANE)
		ret = intersect_plane(ray, shape);
	else if (shape->type == CONE)
		ret = intersect_cone(ray, shape);
	return (ret);
}

void	scene_intersect(t_scene *scene, t_ray *ray)
{
	t_object	*object;
	size_t		i;

	i = 0;
	while (i < scene->objects.len)
	{
		object = (t_object *)vec_get(&scene->objects, i);
		get_shape_intersections(ray, object);
		i++;
	}
}
