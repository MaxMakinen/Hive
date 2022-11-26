/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:57:35 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/14 16:46:06 by jsaarine         ###   ########.fr       */
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

void	push_intersections(t_intersections *intersections, t_ray *ray)
{
	t_intersection	is;
	size_t			i;

	i = intersections->vec.len;
	while (i < ray->xs.vec.len)
	{
		is = *(t_intersection *) vec_get(&ray->xs.vec, i);
		printf("pushing is %lf \n",is.t);
		printf("pushing is %zu \n",is.object->id);
		printf("pushing is%zu \n",is.i);
		vec_push(&intersections->vec, &is);
		i++;
	}
}



t_intersections	scene_intersect(t_scene *scene, t_ray *ray)
{
	t_intersections	intersections;
	t_object		object;
	size_t				i;
	
	vec_new(&intersections.vec, 2, sizeof(t_intersection));
	i = 0;
	while (i < scene->objects.len)
	{
		object = *(t_object *) vec_get(&scene->objects, i);
		if (get_shape_intersections(ray, &object))
			push_intersections(&intersections, ray);
		i++;
	}
	return (intersections);
}