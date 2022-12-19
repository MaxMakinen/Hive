/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:57:35 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/14 18:49:07 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	default_scene(t_scene *scene)
{
	t_light		light;
	t_object	object;

	scene_new(scene);
	light = point_light_new(point_new(-10, 10, -10), color_new(1, 1, 1));
	vec_push(&scene->lights, &light);
	object = object_new(SPHERE);
	object.material.color = color_new(0.8, 1.0, 0.6);
	object.material.diffuse = 0.7;
	object.material.specular = 0.2;
	vec_push(&scene->objects, &object);
	object = object_new(SPHERE);
	object.transform = matrix_scale(0.5, 0.5, 0.5);
	vec_push(&scene->objects, &object);
	return (0);
}

int	scene_new(t_scene *scene)
{
	if (!vec_new(&scene->lights, 6, sizeof(t_light)))
		return (1);
	if (!vec_new(&scene->objects, 6, sizeof(t_object)))
		return (1);
	return (0);
}
