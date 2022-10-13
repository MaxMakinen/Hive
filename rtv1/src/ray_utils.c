/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:26:21 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 15:26:34 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3f	get_intersect(t_vec3f origin, t_vec3f direction, double distance)
{
	t_vec3f	intersect;

	intersect.x = origin.x + direction.x * distance;
	intersect.y = origin.y + direction.y * distance;
	intersect.z = origin.z + direction.z * distance;
	return (intersect);
}

int	check_intersect(t_obj *obj, t_ray *ray, double *temp, double *t1)
{
	if (obj->type == e_sphere)
		return (sphere_intersect(ray, obj, temp, t1));
	else if (obj->type == e_plane)
		return (plane_intersect(ray, obj, temp, t1));
	else if (obj->type == e_cylinder)
		return (cylinder_intersect(ray, obj, temp, t1));
	else if (obj->type == e_cone)
		return (cone_intersect(ray, obj, temp, t1));
	return (FALSE);
}

t_vec3f	get_direction(t_data *data, double x, double y, t_scene *scene)
{
	t_vec3f	direction;

	x /= (data->screen_max.x - 1.0);
	y /= (data->screen_max.y - 1.0);
	direction = vec_minus(vec_plus(vec_plus(scene->lower_left, \
	vec_mult(scene->horizontal, x)), \
	vec_mult(scene->vertical, y)), scene->cam->pos);
	return (direction);
}

t_obj	*get_obj(t_obj *head, enum e_type type)
{
	while (head && head->next != NULL && head->type != type)
		head = head->next;
	if (head->type != type)
		return (NULL);
	else
		return (head);
}
